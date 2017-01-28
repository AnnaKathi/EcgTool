//---------------------------------------------------------------------------
#ifndef classBaseH
#define classBaseH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
enum BASE_ERROR_CODES
	{
	CE_OK,              // no error, all things done well
	CE_HARDERRORS,      // real error codes
						// --------------------------------------------------
	};
//---------------------------------------------------------------------------   
class PACKAGE cBase
    {
public:
    cBase();
	virtual ~cBase();


__property bool     success    = { read=get_success };
__property bool     error      = { read=get_error   };
__property int      error_code = { read=ferror_code };
__property String   error_msg  = { read=ferror_msg  };

__property String   trigger    = { read=ftrigger, write=set_trigger };

protected:
	bool            ferror;
	int             ferror_code;
	String          ferror_msg;

	String          ftrigger;    // set bei view error to the trigger of the error
	void            set_trigger(String value);

    bool            ok();
    bool            fail(const int code, const String& msg);
	bool            fail(const cBase& cb);

private:
    bool            get_success();
    bool            get_error();
    };
#endif

