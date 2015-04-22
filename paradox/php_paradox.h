/*
  +----------------------------------------------------------------------+
  | PHP Version 4                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2003 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Uwe Steinmann <steinm@php.net>                               |
  +----------------------------------------------------------------------+
*/

/* $Id: php_paradox.h,v 1.13 2006/02/21 12:53:51 steinm Exp $ */

#ifndef PHP_PARADOX_H
#define PHP_PARADOX_H

#if HAVE_PARADOX

#include <paradox.h>

typedef struct _paradox_object {
	zend_object zo;
	void *ptr;
} paradox_object; /* extends zend_object */

extern zend_module_entry paradox_module_entry;
#define phpext_paradox_ptr &paradox_module_entry

#ifdef PHP_WIN32
#define PHP_PARADOX_API __declspec(dllexport)
#else
#define PHP_PARADOX_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

zend_class_entry *paradox_pxdoc_class_entry;
#define REGISTER_PARADOX_CLASS(name, parent) \
	{ \
		zend_class_entry ce; \
		INIT_CLASS_ENTRY(ce, "paradox_" # name, paradox_funcs_ ## name); \
		ce.create_object = paradox_object_new_ ## name; \
		paradox_ce_ ## name = zend_register_internal_class_ex(&ce, parent, NULL TSRMLS_CC); \
		memcpy(&paradox_object_handlers_ ## name, zend_get_std_object_handlers(), sizeof(zend_object_handlers)); \
		paradox_object_handlers_ ## name.clone_obj = NULL; \
	}

#define PXDOC_FROM_ZVAL(pxdoc, zv)    ZEND_FETCH_RESOURCE(pxdoc, pxdoc_t *, zv, -1, "px object", le_pxdoc)

#define PXDOC_FROM_OBJECT(pxdoc, object) \
	{ \
		paradox_object *obj = (paradox_object *) zend_object_store_get_object(object TSRMLS_CC); \
		pxdoc = obj->ptr; \
		if (!pxdoc) { \
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "The paradox document wasn't opened"); \
			RETURN_NULL(); \
		} \
	}

#define PX_KEYTOLOWER 1
#define PX_KEYTOUPPER 2

PHP_MINIT_FUNCTION(paradox);
PHP_MSHUTDOWN_FUNCTION(paradox);
PHP_RINIT_FUNCTION(paradox);
PHP_RSHUTDOWN_FUNCTION(paradox);
PHP_MINFO_FUNCTION(paradox);

PHP_FUNCTION(px_new);
PHP_FUNCTION(px_open_fp);
PHP_FUNCTION(px_create_fp);
PHP_FUNCTION(px_close);
PHP_FUNCTION(px_delete);
#ifdef HAVE_PXPACK
PHP_FUNCTION(px_pack);
#endif
PHP_FUNCTION(px_get_record);
PHP_FUNCTION(px_put_record);
#ifdef HAVE_PXDELETERECORD
PHP_FUNCTION(px_delete_record);
#endif
#ifdef HAVE_PXINSERTRECORD
PHP_FUNCTION(px_insert_record);
#endif
#ifdef HAVE_PXUPDATERECORD
PHP_FUNCTION(px_update_record);
#endif
#ifdef HAVE_PXRETRIEVERECORD
PHP_FUNCTION(px_retrieve_record);
#endif
PHP_FUNCTION(px_numrecords);
PHP_FUNCTION(px_numfields);
PHP_FUNCTION(px_get_field);
PHP_FUNCTION(px_get_schema);
PHP_FUNCTION(px_get_info);
PHP_FUNCTION(px_set_parameter);
PHP_FUNCTION(px_get_parameter);
PHP_FUNCTION(px_set_value);
PHP_FUNCTION(px_get_value);
PHP_FUNCTION(px_set_targetencoding);
PHP_FUNCTION(px_set_tablename);
PHP_FUNCTION(px_set_blob_file);
PHP_FUNCTION(px_timestamp2string);
PHP_FUNCTION(px_date2string);

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(paradox)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(paradox)
*/

/* In every utility function you add that needs to use variables 
   in php_paradox_globals, call TSRM_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as PARADOX_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define PARADOX_G(v) TSRMG(paradox_globals_id, zend_paradox_globals *, v)
#else
#define PARADOX_G(v) (paradox_globals.v)
#endif

#else
#define phpext_paradox_ptr NULL
#endif  /* HAVE_PARADOX */

#endif	/* PHP_PARADOX_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
