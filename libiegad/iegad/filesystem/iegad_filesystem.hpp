#ifndef __IEGAD_FILESYSTEM__
#define __IEGAD_FILESYSTEM__



#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <string>




namespace iegad {



class filesystem {
public:
    struct fileInfo {
        fileInfo() :
            type(-1),
            lastWriteTime(0),
            capacity(0),
            free(0),
            available(0),
            used(0)
        {}


        int16_t type;
        std::string name;
        int64_t lastWriteTime;
        int64_t capacity;
        int64_t free;
        int64_t available;
        int64_t used;
    }; // struct fileInfo;


    static const std::string
    find_file(const boost::filesystem::path & dir, const std::string & filename)
    {
        typedef boost::optional<boost::filesystem::path> rzt_t;

        rzt_t res;

        if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir)) {
            return "path is invalied";
        }

        boost::filesystem::recursive_directory_iterator end;
        for (boost::filesystem::recursive_directory_iterator pos(dir); pos != end; pos++) {
            if (!boost::filesystem::is_directory(*pos)
                    && pos->path().filename() == filename) {
                res = pos->path();
            }
        }
        return res ? res->string() : "File not found";
    }


    static const std::vector<fileInfo>
    ls (const std::string & path, std::string * errstr = NULL)
    {
        typedef boost::filesystem::recursive_directory_iterator rd_itr;
        boost::system::error_code ec;
        std::vector<fileInfo> res;
        rd_itr end;
        for (rd_itr pos(path); pos != end; pos++) {
            fileInfo item;
            boost::filesystem::path p(*pos);
            if (boost::filesystem::is_directory(*pos)) {
                pos.no_push();
                boost::filesystem::space_info si = boost::filesystem::space(p, ec);
                if (ec) {
                    if (errstr) {
                        *errstr = ec.message();
                    }
                    break;
                }
                item.type = 0;
                item.capacity = si.capacity;
                item.available = si.available;
                item.free = si.free;
            }
            else {                
                item.type = 1;
                uint64_t used = boost::filesystem::file_size(p, ec);
                item.used = used;
            }
            int64_t tt = boost::filesystem::last_write_time(p);
            item.lastWriteTime = tt;
            item.name = p.string();
            res.push_back(item);
        }
        return res;
    }


    static bool
    mkdir(const boost::filesystem::path & dir, std::string * errstr = NULL)
    {
        boost::system::error_code ec;
        if (boost::filesystem::exists(dir, ec) || ec) {
            if (errstr) {
                *errstr = ec ? ec.message() : "directory is already exists";
            }
            return false;
        }
        boost::filesystem::create_directory(dir, ec);
        if (ec) {
            if (errstr) {
                *errstr = ec.message();
            }
        }
        return !ec;
    }


    static bool
    rename(const boost::filesystem::path & fn, const std::string & newn, std::string * errstr = NULL)
    {
        boost::system::error_code ec;
        if (!boost::filesystem::exists(fn, ec) || ec) {
            if (errstr) {
                *errstr = ec ? ec.message() : "file is not exists";
            }
            return false;
        }
        boost::filesystem::rename(fn, newn, ec);
        if (ec) {
            if (errstr) {
                *errstr = ec.message();
            }
        }
        return !ec;
    }

private:
    filesystem() {}
}; // class filesystem;



} // namespace iegad;



#endif // __IEGAD_FILESYSTEM__
