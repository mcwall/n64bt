#ifndef N64_h
#define N64_h

class N64Controller {
    public:
        N64Controller(unsigned char pincode);
        void init();
        uint32_t status();

    private:
        void send(unsigned char command);
        uint32_t read();
};
#endif
