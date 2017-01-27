//---------------------------------------------------------------------------
#ifndef classBaseH
#define classBaseH
//---------------------------------------------------------------------------
#include <classes.hpp>
//---------------------------------------------------------------------------
enum BASE_ERROR_CODES
	{
	CE_OK,              // no error, all things done well
	CE_SIGNALEOF,       // EOF Signal, no error

    CE_HARDERRORS,      // real error codes
                        // --------------------------------------------------
    CE_NOCASHFILE,      // no cash file avaliable
    CE_CANTOPEN,        // can't open cashfile
    CE_FILEERROR,       // can't seek or read from file
    CE_WRITEERROR,      // can't write to file
    CE_FILECORRUPT,     // unexpected record, can't seek to KAID
    CE_UNEXPECTEOF,     // unexpected eof in next_rec, kasse_t-record expected

    CE_EXCEPTION,       // exception raised
    CE_UNKNOWN,         // unknown error
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

