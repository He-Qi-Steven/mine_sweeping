#ifndef SOCKET_MESSAGE_HQ_H
#define SOCKET_MESSAGE_HQ_H

#define BUFFER_MAX_LEN 512

typedef struct
{
    unsigned char type;
    unsigned char length;//一个 value 长度最大 256 Bytes
}TLV_HEADER;

typedef struct
{
    TLV_HEADER header;
    void * value;
}TLV;

#endif // SOCKET_MESSAGE_HQ_H
