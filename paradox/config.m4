dnl $Id: config.m4,v 1.11 2006/02/21 12:54:16 steinm Exp $
dnl config.m4 for extension paradox

PHP_ARG_WITH(paradox, for paradox support,
Option to configure paradox extension:
[  --with-paradox[=DIR]    Include paradox support])

if test "$PHP_PARADOX" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-paradox -> check with-path
  SEARCH_PATH="/usr/local /usr"     # you might want to change this
  SEARCH_FOR="include/paradox.h"  # you most likely want to change this
  if test -r $PHP_PARADOX/$SEARCH_FOR; then # path given as parameter
    PARADOX_DIR=$PHP_PARADOX
  else # search default path list
    AC_MSG_CHECKING([for paradox files in default path])
    for i in $SEARCH_PATH ; do
      if test -r $i/$SEARCH_FOR; then
        PARADOX_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi

  if test -z "$PARADOX_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([Please reinstall the paradox distribution])
  fi

  PHP_ADD_INCLUDE($PARADOX_DIR/include)

  LIBNAME=px # you may want to change this
  LIBSYMBOL=PX_create_blob_fp # you most likely want to change this 

  PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  [
  	AC_CHECK_LIB($LIBNAME, PX_insert_record, AC_DEFINE(HAVE_PXINSERTRECORD,1,[pxlib 0.6.0 or later]))
  	AC_CHECK_LIB($LIBNAME, PX_update_record, AC_DEFINE(HAVE_PXUPDATERECORD,1,[pxlib 0.6.0 or later]))
  	AC_CHECK_LIB($LIBNAME, PX_retrieve_record, AC_DEFINE(HAVE_PXRETRIEVERECORD,1,[pxlib 0.6.0 or later]))
  	AC_CHECK_LIB($LIBNAME, PX_delete_record, AC_DEFINE(HAVE_PXDELETERECORD,1,[pxlib 0.6.0 or later]))
  	AC_CHECK_LIB($LIBNAME, PX_pack, AC_DEFINE(HAVE_PXPACK,1,[pxlib 0.6.1 or later]))
    PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PARADOX_DIR/lib, PARADOX_SHARED_LIBADD)
    AC_DEFINE(HAVE_PARADOXLIB,1,[ ])
  ],[
    AC_MSG_ERROR([wrong paradox lib version or lib not found. Need at least pxlib 0.6.0])
  ],[
    -L$PARADOX_DIR/lib -lm -ldl
  ])

  PHP_SUBST(PARADOX_SHARED_LIBADD)

  AC_DEFINE(HAVE_PARADOX,1,[Whether to include the paradox extension])
  PHP_NEW_EXTENSION(paradox, paradox.c, $ext_shared)
fi

AC_ARG_WITH(paradox-memdebug,
[  --with-paradox-memdebug Enable paradox memory debugging],[
  if test "$withval" = "yes"; then
    AC_DEFINE(PARADOX_MEMDEBUG,1,[Paradox extension debugging])
  fi
])
