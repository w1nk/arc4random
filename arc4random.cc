/*
 * Copyright (c) 2014 Thomas Cort <linuxgeek@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#define __STDC_LIMIT_MACROS

#include <node.h>
#include <node_buffer.h>
#include <v8.h>

#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef USE_LIBBSD
#include <bsd/stdlib.h>
#endif

using namespace v8;
using namespace node;

Handle<Value> node_arc4random(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 0) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}

	return scope.Close(Uint32::NewFromUnsigned(arc4random()));
}

Handle<Value> node_arc4random_buf(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}

	if (!Buffer::HasInstance(args[0]) || !args[1]->IsNumber() || isnan(args[1]->NumberValue()) || args[1]->IntegerValue() < 0 || args[1]->IntegerValue() > UINT32_MAX) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

	Local<Object> bufferObj    = args[0]->ToObject();
	char*  bufferData   = Buffer::Data(bufferObj);
	size_t bufferLength = Buffer::Length(bufferObj);
	size_t nbytes = args[1]->IntegerValue();

	if (bufferLength < nbytes) {
		nbytes = bufferLength; // don't overrun the buffer.
	}

	arc4random_buf(bufferData, nbytes);

	return scope.Close(Undefined());
}

Handle<Value> node_arc4random_uniform(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1) {
		ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
		return scope.Close(Undefined());
	}

	if (!args[0]->IsNumber() || isnan(args[0]->NumberValue()) || args[0]->IntegerValue() < 0 || args[0]->IntegerValue() > UINT32_MAX) {
		ThrowException(Exception::TypeError(String::New("Wrong arguments")));
		return scope.Close(Undefined());
	}

	return scope.Close(Number::New(arc4random_uniform(args[0]->Uint32Value())));
}

void init(Handle<Object> exports) {
	Context::GetCurrent()->Global()->Set(String::NewSymbol("arc4random"), FunctionTemplate::New(node_arc4random)->GetFunction());
	Context::GetCurrent()->Global()->Set(String::NewSymbol("arc4random_buf"), FunctionTemplate::New(node_arc4random_buf)->GetFunction());
	Context::GetCurrent()->Global()->Set(String::NewSymbol("arc4random_uniform"), FunctionTemplate::New(node_arc4random_uniform)->GetFunction());
}

NODE_MODULE(arc4random, init)
