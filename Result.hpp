
#include <cassert>

template <typename T = void, typename E = void>
struct Result {
private:

    bool _ok;
    T _data;
    E _err;

public:

    Result () {
        *this = Fail();
    }

    Result(E err)
        : _ok(true), _err(err) {
    }

    Result(T data)
        : _ok(true), _data(data) {
    }

    operator T() {
        return this->get();
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
        assert(_ok); return _data;
    }

    const T& getOr(const T& data) const {
        return _ok ? _data : data;
    }

    const E& getErr() const {
        assert(!_ok); return _err;
    }
};

template <typename T>
struct Result<T, T> {
private:
    using ResultContent = T;

    bool _ok;
    ResultContent _data;

public:

    Result () {
        *this = Fail();
    }

    Result (T data)
        : Result(true, data) {
    }

    Result(bool ok, T data)
        : _ok(ok), _data(data) {
    }

    operator T(){
        return this->get();
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
        assert(_ok); return _data;
    }

    const T& getOr(const T& data) const {
        return _ok ? _data : data;
    }

    const T& getErr() const {
        assert(!_ok); return _data;
    }
};


template <typename T>
struct Result<T, void> {
private:
    using ResultContent = T;

    bool _ok;
    ResultContent _data;

public:

    Result()
        : _ok(false) {
    }

    Result(T data)
        : _ok(true), _data(data) {
    }

    operator T(){
        return this->get();
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
        assert(_ok); return _data;
    }

    const T& getOr(const T& data) const {
        return _ok ? _data : data;
    }
};

template <typename E>
struct Result<void, E> {
private:

    bool _ok;
    E _err;

public:

    Result()
        : _ok(false) {
    }

    Result(E err)
        : _ok(false), _err(err) {
    }

    static Result Succ(){
        Result a;
        a._ok = true;
        return a;
    }

    static Result Fail(){
        return Result();
    }

    static Result Fail(E data){
        return Result(data);
    }

    bool ok() const {
        return _ok;
    }

    const E& getErr() const {
        assert(!_ok); return _err;
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
