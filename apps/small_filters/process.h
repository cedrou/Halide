#ifndef PROCESS_H
#define PROCESS_H

enum bmark_run_mode_t {
    hvx64 = 1,
    hvx128 = 2,
    cpu = 3
};


typedef int (*pipeline2)(buffer_t *, buffer_t *);
typedef int (*pipeline3)(buffer_t *, buffer_t *, buffer_t *);

struct PipelineDescriptorBase {
    virtual void identify_pipeline() = 0;
    virtual void init() = 0;
    virtual int run(bmark_run_mode_t mode) = 0;
    virtual bool verify(int W, int H) = 0;
};

template <typename T1, typename T2>
struct PipelineDescriptor : public PipelineDescriptorBase  {
    T1 pipeline_64, pipeline_128, pipeline_cpu;
 
    PipelineDescriptor(T1 pipeline_64, T1 pipeline_128, T1 pipeline_cpu) :
    pipeline_64(pipeline_64), pipeline_128(pipeline_128), pipeline_cpu(pipeline_cpu) {}
 
    void identify_pipeline() {
        static_cast<T2*>(this)->identify_pipeline();
    }
    void init() {
        static_cast<T2*>(this)->init();
    }
    int run(bmark_run_mode_t mode) {
        return static_cast<T2*>(this)->run(mode);
    }
    bool verify(int W, int H) {
        return static_cast<T2*>(this)->verify(W, H);
    }
};


#endif