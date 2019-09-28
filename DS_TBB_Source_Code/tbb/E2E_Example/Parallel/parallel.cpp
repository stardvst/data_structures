#include "Parallel\ParallelRepository.h"
#include "ocr_pipeline.h"

std::unique_ptr<ReviewRepository> run_parallel(int count){
    OcrPipeline pipeline(count);
    
    std::unique_ptr<ReviewRepository> repository(new ParallelRepository());

    pipeline.run([&repository](const Review& review){
        repository->save(review);
    });

    return std::move(repository);
}
