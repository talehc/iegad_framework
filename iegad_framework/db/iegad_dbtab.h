#ifndef __IEGAD_DBTAB__
#define __IEGAD_DBTAB__



// ============ 说明 ============
//
// @创建日期 : 2015-10-03
// @创建人 : iegad
//
// ============================
// @用途 :  数据库访问操作时, 用来存储表的对象, 模访C#中的DataTable
// ============================
//
// @修改记录:
// =======================================
//  日期                     修改人                                   修改说明
// =======================================



#include "iegad_dbrow.h"
#include <vector>


namespace iegad {
namespace db {


    class db_tab {
    // 数据表
    public:	
	// ============================
	// @用途 : 将 数据行的向量 视为数据表 类型声明
	// ============================
	typedef std::vector<dbrow_ptr> rows_t;


	// ============================
	// @用途 : 构造函数
	// ============================
	explicit db_tab() {}


	// ============================
	// @用途 : 构造函数
	// @PS : 在对象释放时, 会清除所有的行.
	// ============================
	~db_tab() {
	    this->clear();
	}


	// ============================
	// @用途 : [] 运算符重载, 用来访问 数据行的智能指针对象
	// @col_num : 列的索引
	// @返回值 : 该列所包含的值
	// ============================
	dbrow_ptr operator[](int rownum);

	// ============================
	// @用途 : 添加一列
	// @row : 需要添加的行的智能指针
	// @返回值 : void
	// ============================
	void add_row(dbrow_ptr & row);


	// ============================
	// @用途 : 清除所有行的信息
	// @返回值 : void
	// ============================
	void clear();


	// ============================
	// @用途 : 返回行的总数
	// @返回值 : 表中行的总数
	// ============================
	int row_count() const;

    private:
	// 表对象 (行的集合)
	rows_t tab_;

	// 禁用
	db_tab(db_tab &);
	db_tab & operator=(db_tab &);
    }; // class db_tab;


    // db_tab 的智能指针类型
    typedef std::shared_ptr<db_tab> dbtab_ptr;


} // namespace db;
} // namespace iegad;


#endif // __IEGAD_DBTAB__