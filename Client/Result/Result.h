#pragma once

#include <string>
#include <functional>

enum class ResultStatus {
    OKAY,
    ERR,
    WARNING
};

class Result {
public:
    Result(ResultStatus status, std::string message = "") : status_(status), message_(std::move(message)), customFormat_(nullptr) {};

    ResultStatus status() const { return status_; };
    const std::string& message() const { return message_; };

    void setCustomFormat(std::function<std::string(const Result&)> formatFunc) {
        customFormat_ = formatFunc;
    };

    std::string toString() const {
        if (customFormat_) {
            return customFormat_(*this);
        };
        switch (status_) {
            case ResultStatus::OKAY: return "OKAY: " + message_;
            case ResultStatus::ERR: return "ERROR: " + message_;
            case ResultStatus::WARNING: return "WARNING: " + message_;
            default: return "UNKNOWN STATUS: " + message_;
        };
    };

    operator std::string() const { return toString(); };

    bool operator==(ResultStatus other) const { return status_ == other; };
    bool operator!=(ResultStatus other) const { return status_ != other; };
private:
    std::function<std::string(const Result&)> customFormat_;
    ResultStatus status_;
    std::string message_;
};