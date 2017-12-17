
#include <cassert>

template <typename T = void, typename E = void>
struct Result {
private:
    union ResultContent {
        T data;
        E error;
    };

    bool _ok;
    ResultContent _content;

public:

    Result () {
        *this = Fail();
    }

    Result(E err)
        : _ok(true), _content({err}) {
    }

    Result(T data)
        : _ok(true), _content({data}) {
    }

    static Result Succ(){
        T data;
        return Result(data);
    }

    static Result Fail(){
        E err;
        return Result(err);
    }

    static Result Succ(T data){
        return Result(data);
    }

    static Result Fail(E err){
        return Result(err);
    }

    bool ok() {
        return _ok;
    }

    const T& get() const {
        assert(_ok); return _content.data;
    }

    const T& getOr(const T& data) const {
        return _ok ? _content.data : data;
    }

    const E& getErr() const {
        assert(!_ok); return _content.err;
    }
};

template <typename T>
struct Result<T, T> {
private:
    using ResultContent = T;

    bool _ok;
    ResultContent _content;

public:

    Result () {
        *this = Fail();
    }

    Result(bool ok, T data)
        : _ok(ok), _content(data) {
    }

    static Result Succ(){
        T data;
        return Result(true, data);
    }

    static Result Fail(){
        T err;
        return Result(false, err);
    }

    static Result Succ(T data){
        return Result(true, data);
    }

    static Result Fail(T err){
        return Result(false, err);
    }

    bool ok() const {
        return _ok;
    }

    const T& get() const {
        assert(_ok); return _content;
    }

    const T& getOr(const T& data) const {
        return _ok ? _content.data : data;
    }

    const T& getErr() const {
        assert(!_ok); return _content;
    }
};


template <typename T>
struct Result<T, void> {
private:
    using ResultContent = T;

    bool _ok;
    ResultContent _content;

public:

    Result()
        : _ok(false) {
    }

    Result(T data)
        : _ok(true), _content(data) {
    }

    static Result Succ(){
        T data;
        return Result(data);
    }

    static Result Fail(){
        return Result();
    }

    static Result Succ(T data){
        return Result(data);
    }

    bool ok() const {
        return _ok;
    }

    const T& get() const {
        assert(_ok); return _content;
    }

    const T& getOr(const T& data) const {
        return _ok ? _content.data : data;
    }
};

template <typename T>
struct Result<void, T> {
private:
    using ResultContent = T;

    bool _ok;
    ResultContent _content;

public:

    Result()
        : _ok(false) {
    }

    Result(T data)
        : _ok(false), _content(data) {
    }

    static Result Succ(){
        Result a;
        a._ok = true;
        return a;
    }

    static Result Fail(){
        return Result();
    }

    static Result Fail(T data){
        return Result(data);
    }

    bool ok() const {
        return _ok;
    }

    const T& getErr() const {
        assert(!_ok); return _content;
    }
};

template <>
struct Result<void, void> {
private:
    bool _ok;

public:

    Result()
        : Result(false){
    }

    Result(bool ok)
        : _ok(ok) {
    }

    static Result Succ(){
        return Result(true);
    }

    static Result Fail(){
        return Result(false);
    }

    bool ok() const {
        return _ok;
    }
};
