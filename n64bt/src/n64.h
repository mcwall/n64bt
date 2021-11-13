#ifndef N64_h
#define N64_h

class N64 {
    public:
        N64(unsigned char pincode);
        virtual void init();
        virtual void send(unsigned char command);
        virtual void get();

        char raw_dump[33];
};
#endif
