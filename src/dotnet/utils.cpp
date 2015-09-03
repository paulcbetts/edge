#include "edge.h"

Handle<v8::String> stringCLR2V8(System::String^ text)
{
    Nan::EscapableHandleScope scope;
    if (text->Length > 0)
    {
        array<unsigned char>^ utf8 = System::Text::Encoding::UTF8->GetBytes(text);
        pin_ptr<unsigned char> ch = &utf8[0];
        return scope.Escape(Nan::New<v8::String>((char*)ch)).ToLocalChecked();
    }
    else
    {
        return scope.Escape(Nan::New<v8::String>("").ToLocalChecked());
    }
}

System::String^ stringV82CLR(Handle<v8::String> text)
{
    Nan::HandleScope scope;
    String::Utf8Value utf8text(text);
    if (*utf8text)
    {
        return gcnew System::String(
            *utf8text, 0, utf8text.length(), System::Text::Encoding::UTF8);
    }
    else
    {
        return System::String::Empty;
    }
}

System::String^ exceptionV82stringCLR(Handle<v8::Value> exception)
{
    Nan::HandleScope scope;
    if (exception->IsObject())
    {
        Handle<Value> stack = exception->ToObject()->Get(Nan::New<v8::String>("stack").ToLocalChecked());
        if (stack->IsString())
        {
            return gcnew System::String(stringV82CLR(stack->ToString()));
        }
    }

    return gcnew System::String(stringV82CLR(Handle<v8::String>::Cast(exception)));
}

Handle<Value> throwV8Exception(Handle<Value> exception)
{
    Nan::EscapableHandleScope scope;
    Nan::ThrowError(exception);
    return scope.Escape(exception);
}
