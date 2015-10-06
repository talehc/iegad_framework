#ifndef __SERVICE_BASIC__
#define __SERVICE_BASIC__



// ============ ˵�� ============
//
// @�������� : 2015-10-01
// @������ : iegad
//
// ============================
// @��; : �÷������, �����з��������Ļ���, 
//		1. ͳһ���ýӿ�
//		2. �ṩһЩ�����ĺ���
// ============================
//
// @�޸ļ�¼:
// =======================================
//  ����                     �޸���                                   �޸�˵��
// =======================================




#include <string>
#include <memory>
#include <unordered_map>
#include "net/iegad_io_msg.h"


namespace iegad {
namespace net {

    
    class svc_basic {
    // ������������, ������;
    public:
	// ============================
	// @��; : �౾��������ָ�� ��������
	// ============================
	typedef std::shared_ptr<svc_basic> svc_basic_ptr;


	// ============================
	// @��; : "����ID �������� ӳ���" ��������
	// ============================
	typedef std::unordered_map<int, svc_basic_ptr> svc_map_t;
	

	// ============================
	// @��; : �� ӳ��� svc_map ���ҵ� ��Ӧ svc_id �ķ������ָ��
	// @svc_id : ����ID
	// @svc_map : ӳ���
	// @����ֵ : �ɹ����� svc��������ָ��, ����, ����һ��nullptr������ָ��
	// ============================
	static svc_basic_ptr get_svc(int svc_id, svc_map_t & svc_map);


	// ============================
	// @��; : �� ������� svc_obj �ӵ� ӳ��� svc_map ��;
	// @svc_obj : ������������ָ��
	// @svc_map : ӳ���
	// @����ֵ : �ɹ����� 0, ���򷵻� -1; 
	// @PS : ��������ֻ���� ����������� ������ͬ�ķ���ID;
	// ============================
	static int regist_svc(const svc_basic_ptr & svc_obj, svc_map_t & svc_map);


	// ============================
	// @��; : ִ�� tcp�ͻ��� clnt �����͵��������;
	// @clnt : ��������tcp�ͻ���;
	// @msg_flag : ��Ϣ��־ msg_baisc::msg_flag
	// @msg_bdstr : ����Ϣ�Ĺ����ַ���
	// @����ֵ : ���óɹ����� 0, ���򷵻� -1; 
	// @PS : �������ĵ��ýӿ�, �ú���Ϊ���麯��, ��ʵ�ʵķ������(������)ʵ��;
	// ============================
	virtual int action(boost::asio::ip::tcp::socket & clnt, int msg_flag, const std::string & msg_bdstr) = 0;


	// ============================
	// @��; : ���ظö���ķ���ID
	// @����ֵ : ���ط���ID
	// ============================
	int get_id();

    protected:
	// ============================
	// @��; : ���캯��
	// @svc_id : ����ID
	// ============================
	explicit svc_basic(int svc_id);


	// ============================
	// @��; : ��������
	// ============================
	virtual ~svc_basic() {}


	// ============================
	// @��; : ͨ�� ����Ϣ�����ַ��� msgbdstr ������ ����Ϣ msg;
	// @msgbdstr : ����Ϣ�Ĺ����ַ���
	// @msg : ����Ϣ����
	// @����ֵ, �ɹ���������0, ����, ����-1;
	// @PS : ģ����� __MSG_T һ��Ҫ����google protocol buffer
	//		�����ɵ�msg��������.
	// ============================
	template <class __MSG_T> 
	int _build_svc(const std::string & msgbdstr, __MSG_T & msg);


	// ============================
	// @��; : ��tcp�ͻ��� clnt ���� ��Ϣ msg;
	// @clnt : tcp �ͻ���
	// @flag : ��Ϣ��־, msg_basic::msg_flag
	// @msg : ����Ϣ����;
	// @����ֵ, ���ͳɹ�����0, ����, ����-1;
	// @PS : ģ����� __MSG_T һ��Ҫ����google protocol buffer
	//		�����ɵ�msg��������.
	// ============================
	template <class __MSG_T>
	int _send_msg(boost::asio::ip::tcp::socket & clnt, int flag, const __MSG_T & msg);


	// ============================
	// @��; : ��tcp�ͻ��� clnt ����Ӧ��;;
	// @clnt : tcp �ͻ���
	// @rzt : Ӧ��Ľ��, �������Լ�����
	// @rzt_size : Ӧ�����ݵĳ���
	// @����ֵ, ���ͳɹ����͵��ֽ���
	// @PS : Ϊ�����ͨ�ŴӶ����Ӹú���, ���������
	//		ÿ��Ӧ��ʱ, ������һ��msg_basic����;
	// ============================
	int _response(boost::asio::ip::tcp::socket & clnt, const char * rzt, size_t rzt_size);

    private:
	// ����ID
	int svc_id_;
    }; // class svc_basic



// ==================  ����Ϊʵ�ֲ��� ==================


    template <class __MSG_T>
    int iegad::net::svc_basic::_build_svc(const std::string & msgbdstr, __MSG_T & msg)
    {
	msg.Clear();
	return msg.ParseFromString(msgbdstr) ? 0 : -1;
    }


    template <class __MSG_T>
    int iegad::net::svc_basic::_send_msg(boost::asio::ip::tcp::socket & clnt, int flag, const __MSG_T & msg)
    {
	std::string msg_str;

	if (!msg.SerializeToString(&msg_str)) {
	    return -1;
	}

	msg_basic msgbsc;
	msgbsc.set_msg_type(this->svc_id_);
	msgbsc.set_msg_flag(flag);
	msgbsc.set_msg_bdstr(msg_str);
	return iegad::net::send_msg_basic(clnt, msgbsc);
    }


} // namespace net;
} // namespace iegad;


#endif // __SERVICE_BASIC__