
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/exception.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/object.h"
#include "kernel/operators.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Cache\Multiple
 *
 * Allows to read to chained backends writing to multiple backends
 *
 *<code>
 *   use Phalcon\Cache\Frontend\Data as DataFrontend,
 *       Phalcon\Cache\Multiple,
 *       Phalcon\Cache\Backend\Apc as ApcCache,
 *       Phalcon\Cache\Backend\Memcache as MemcacheCache,
 *       Phalcon\Cache\Backend\File as FileCache;
 *
 *   $ultraFastFrontend = new DataFrontend(array(
 *       "lifetime" => 3600
 *   ));
 *
 *   $fastFrontend = new DataFrontend(array(
 *       "lifetime" => 86400
 *   ));
 *
 *   $slowFrontend = new DataFrontend(array(
 *       "lifetime" => 604800
 *   ));
 *
 *   //Backends are registered from the fastest to the slower
 *   $cache = new Multiple(array(
 *       new ApcCache($ultraFastFrontend, array(
 *           "prefix" => 'cache',
 *       )),
 *       new MemcacheCache($fastFrontend, array(
 *           "prefix" => 'cache',
 *           "host" => "localhost",
 *           "port" => "11211"
 *       )),
 *       new FileCache($slowFrontend, array(
 *           "prefix" => 'cache',
 *           "cacheDir" => "../app/cache/"
 *       ))
 *   ));
 *
 *   //Save, saves in every backend
 *   $cache->save('my-key', $data);
 *</code>
 */
ZEPHIR_INIT_CLASS(Phalcon_Cache_Multiple) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Cache, Multiple, phalcon, cache_multiple, phalcon_cache_multiple_method_entry, 0);

	zend_declare_property_null(phalcon_cache_multiple_ce, SL("_backends"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Phalcon\Cache\Multiple constructor
 *
 * @param	Phalcon\Cache\BackendInterface[] backends
 */
PHP_METHOD(Phalcon_Cache_Multiple, __construct) {

	zval *backends = NULL, *_0, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &backends);

	if (!backends) {
		backends = ZEPHIR_GLOBAL(global_null);
	}


	if ((Z_TYPE_P(backends) != IS_NULL)) {
		if ((Z_TYPE_P(backends) != IS_ARRAY)) {
			ZEPHIR_INIT_VAR(_0);
			object_init_ex(_0, phalcon_cache_exception_ce);
			ZEPHIR_INIT_VAR(_1);
			ZVAL_STRING(_1, "The backends must be an array", 1);
			zephir_call_method_p1_noret(_0, "__construct", _1);
			zephir_throw_exception(_0 TSRMLS_CC);
			ZEPHIR_MM_RESTORE();
			return;
		}
		zephir_update_property_this(this_ptr, SL("_backends"), backends TSRMLS_CC);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Adds a backend
 *
 * @param Phalcon\Cache\BackendInterface backend
 * @return Phalcon\Cache\Multiple
 */
PHP_METHOD(Phalcon_Cache_Multiple, push) {

	zval *backend, *_0 = NULL, *_1;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &backend);



	if (zephir_is_instance_of(backend, SL("Phalcon\\Cache\\BackendInterface") TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(_0);
		object_init_ex(_0, spl_ce_BadMethodCallException);
		ZEPHIR_INIT_VAR(_1);
		ZVAL_STRING(_1, "Parameter 'backend' must be an instance of 'Phalcon\\Cache\\BackendInterface'", 1);
		zephir_call_method_p1_noret(_0, "__construct", _1);
		zephir_throw_exception(_0 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	if ((Z_TYPE_P(backend) != IS_OBJECT)) {
		ZEPHIR_INIT_LNVAR(_0);
		object_init_ex(_0, phalcon_cache_exception_ce);
		ZEPHIR_INIT_BNVAR(_1);
		ZVAL_STRING(_1, "The backend is not valid", 1);
		zephir_call_method_p1_noret(_0, "__construct", _1);
		zephir_throw_exception(_0 TSRMLS_CC);
		ZEPHIR_MM_RESTORE();
		return;
	}
	zephir_update_property_this(this_ptr, SL("_backends"), backend TSRMLS_CC);
	RETURN_THIS();

}

/**
 * Returns a cached content reading the internal backends
 *
 * @param 	string|int keyName
 * @param   long lifetime
 * @return  mixed
 */
PHP_METHOD(Phalcon_Cache_Multiple, get) {

	HashTable *_2;
	HashPosition _1;
	zval *keyName, *lifetime = NULL, *backend = NULL, *content = NULL, *_0, **_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &keyName, &lifetime);

	if (!lifetime) {
		lifetime = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_backends"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
	  ; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(backend, _3);
		ZEPHIR_INIT_NVAR(content);
		zephir_call_method_p2(content, backend, "get", keyName, lifetime);
		if ((Z_TYPE_P(content) != IS_NULL)) {
			RETURN_CCTOR(content);
		}
	}
	RETURN_MM_NULL();

}

/**
 * Starts every backend
 *
 * @param string|int keyName
 * @param long lifetime
 */
PHP_METHOD(Phalcon_Cache_Multiple, start) {

	HashTable *_2;
	HashPosition _1;
	zval *keyName, *lifetime = NULL, *backend = NULL, *_0, **_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &keyName, &lifetime);

	if (!lifetime) {
		lifetime = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_backends"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
	  ; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(backend, _3);
		zephir_call_method_p2_noret(backend, "start", keyName, lifetime);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Stores cached content into all backends and stops the frontend
 *
 * @param string keyName
 * @param string content
 * @param long lifetime
 * @param boolean stopBuffer
 */
PHP_METHOD(Phalcon_Cache_Multiple, save) {

	HashTable *_2;
	HashPosition _1;
	zval *keyName = NULL, *content = NULL, *lifetime = NULL, *stopBuffer = NULL, *backend = NULL, *_0, **_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 4, &keyName, &content, &lifetime, &stopBuffer);

	if (!keyName) {
		keyName = ZEPHIR_GLOBAL(global_null);
	}
	if (!content) {
		content = ZEPHIR_GLOBAL(global_null);
	}
	if (!lifetime) {
		lifetime = ZEPHIR_GLOBAL(global_null);
	}
	if (!stopBuffer) {
		stopBuffer = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_backends"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
	  ; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(backend, _3);
		zephir_call_method_p4_noret(backend, "save", keyName, content, lifetime, stopBuffer);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Deletes a value from each backend
 *
 * @param string|int keyName
 * @return boolean
 */
PHP_METHOD(Phalcon_Cache_Multiple, delete) {

	HashTable *_2;
	HashPosition _1;
	zval *keyName, *backend = NULL, *_0, **_3;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &keyName);



	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_backends"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
	  ; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(backend, _3);
		zephir_call_method_p1_noret(backend, "delete", keyName);
	}
	RETURN_MM_BOOL(1);

}

/**
 * Checks if cache exists in at least one backend
 *
 * @param  string|int keyName
 * @param  long lifetime
 * @return boolean
 */
PHP_METHOD(Phalcon_Cache_Multiple, exists) {

	HashTable *_2;
	HashPosition _1;
	zval *keyName = NULL, *lifetime = NULL, *backend = NULL, *_0, **_3, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &keyName, &lifetime);

	if (!keyName) {
		keyName = ZEPHIR_GLOBAL(global_null);
	}
	if (!lifetime) {
		lifetime = ZEPHIR_GLOBAL(global_null);
	}


	_0 = zephir_fetch_nproperty_this(this_ptr, SL("_backends"), PH_NOISY_CC);
	zephir_is_iterable(_0, &_2, &_1, 0, 0);
	for (
	  ; zend_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HVALUE(backend, _3);
		ZEPHIR_INIT_NVAR(_4);
		zephir_call_method_p2(_4, backend, "exists", keyName, lifetime);
		if (ZEPHIR_IS_TRUE(_4)) {
			RETURN_MM_BOOL(1);
		}
	}
	RETURN_MM_BOOL(0);

}
