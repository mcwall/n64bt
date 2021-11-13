#ifndef N64_h
#define N64_h

class N64 {
    public:
        N64(unsigned char pincode);
        void init();
        uint32_t get();

    private:
        void send(unsigned char command);
        uint32_t read();
};
#endif
