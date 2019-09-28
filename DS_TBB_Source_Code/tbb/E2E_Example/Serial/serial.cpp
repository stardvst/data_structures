#include "Scanner\Scanner.h"
#include "ocr\OcrEngine.h"
#include "OcrReviewParser.h"
#include "Serial\SerialRepository.h"
#include "sentiment\SentimentAnalyzer.h"

std::unique_ptr<ReviewRepository> run_serial(int count) {
    Scanner scanner(count);
    OcrEngine ocr;
    OcrReviewParser ReviewerParser;
    SerialRepository* repository = new SerialRepository();
    SentimentAnalyzer sentimentAnalyzer;
    Image image;

    while (scanner.try_acquire(&image)) {
        auto ocrResult = ocr.parse(image.get_bytes(), image.size());
        auto review = ReviewerParser.parse(ocrResult);
        review.review.Sentiment = sentimentAnalyzer.analyze(review);
        repository->save(review);
    }

    return std::move(std::unique_ptr<ReviewRepository>(repository));
}
