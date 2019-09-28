#pragma once

#include <memory>
#include "tbb/tbb.h"
#include "Scanner\Scanner.h"
#include "ocr\OcrEngine.h"
#include "OcrReviewParser.h"
#include "sentiment\SentimentAnalyzer.h"

class OcrPipeline {
    Scanner scanner;
    OcrEngine ocr;
    OcrReviewParser reviewerParser;
    SentimentAnalyzer sentimentAnalyzer;

public:
    OcrPipeline(int count) : scanner(count) {}

    template<class Func>
    void run(Func callback) {

        tbb::parallel_pipeline(
            8,
            tbb::make_filter<void, Image>(
            tbb::filter::serial_in_order, 
            [&](tbb::flow_control& flow) -> Image { 
                Image img;
                if (scanner.try_acquire(&img)) {
                    return std::move(img);
                }
                flow.stop();
                return img;
            })
            &
            tbb::make_filter<Image, OcrResult>(
            tbb::filter::parallel, [this](Image image){
                return std::move(ocr.parse(image.get_bytes(), image.size()));
            })
            &
            tbb::make_filter<OcrResult, Review>(
            tbb::filter::parallel, [this](OcrResult ocrResult) {
                 return std::move(reviewerParser.parse(ocrResult));
            })
            &
            tbb::make_filter<Review, Review>(
            tbb::filter::parallel, [this](Review review) {
                review.review.Sentiment = sentimentAnalyzer.analyze(review);
                return std::move(review);
            })
            &
            tbb::make_filter<Review, void>(
            tbb::filter::parallel, [&callback](Review review) {
                callback(std::move(review));
            })
         );
    }
};