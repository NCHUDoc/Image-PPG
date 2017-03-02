#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H


//#include <errno.h>


#include <QString>
#include <QObject>
#include <QTextCodec>

#define CLEAR(x) memset(&(x), 0, sizeof(x))

class VideoDevice : public QObject
{
    Q_OBJECT
public:
    VideoDevice(QString dev_name);
    ~VideoDevice();

    //int get_frame(unsigned char **yuv_buffer_pointer, size_t* len)
    int get_frame(unsigned char **yuv_buffer_pointer, size_t len);
    int unget_frame();



private:
    int open_device();
    int init_device();
    int start_capturing();
    int init_mmap();
    int stop_capturing();
    int uninit_device();
    int close_device();

    struct buffer
    {
        void * start;
        size_t length;
    };
    QString dev_name;
    int fd;//video0 file
    buffer* buffers;
    unsigned int n_buffers;
    int index;


signals:
    //void display_error(QString);

};



#endif // VIDEODEVICE_H
