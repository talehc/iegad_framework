#ifndef __IEGAD_TCP_SESSION__
#define __IEGAD_TCP_SESSION__



#include <string>
#include <memory.h>
#include <unistd.h>



namespace iegad {
namespace net {


class tcp_session {
public:
    explicit tcp_session(int sockfd)
        :
        sockfd_(sockfd) {
        memset(&addr_, 0, sizeof(addr_));
    }

    ~tcp_session() {
        if (sockfd_ != -1) {
            close(sockfd_);
        }
    }

    int sockfd() const {
        return sockfd_;
    }


    void reset_sockfd() {
        if (sockfd_ != -1) {
            close(sockfd_);
            sockfd_ = -1;
        }
    }

    const sockaddr_in & addr() const {
        return addr_;
    }


    std::string & msgbuff() {
        return msgbuff_;
    }

    void setMsgbuff(const std::string &msgbuff) {
        msgbuff_ = msgbuff;
    }


private:
    int sockfd_;
    sockaddr_in addr_;
    std::string msgbuff_;
};


 // class tcp_session;


} // namespace net;
} // namespace iegad;



#endif // __IEGAD_TCP_SESSION__