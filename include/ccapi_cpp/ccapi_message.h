#ifndef INCLUDE_CCAPI_CPP_CCAPI_MESSAGE_H_
#define INCLUDE_CCAPI_CPP_CCAPI_MESSAGE_H_
#include <vector>
#include <chrono>
//  include <string>
#include "ccapi_cpp/ccapi_correlationId.h"
#include "ccapi_cpp/ccapi_element.h"
#include "ccapi_cpp/ccapi_logger.h"
// #include "ccapi_cpp/ccapi_generic_base.h"
namespace ccapi {
class Message final {
 public:
  enum class RecapType {
    UNKNOWN,
    NONE,  // normal data tick; not a recap
    SOLICITED  // generated on request by subscriber
  };
  static std::string recapTypeToString(RecapType recapType) {
    std::string output;
    switch (recapType) {
      case RecapType::UNKNOWN:
        output = "UNKNOWN";
        break;
      case RecapType::NONE:
        output = "NONE";
        break;
      case RecapType::SOLICITED:
        output = "SOLICITED";
        break;
      default:
        CCAPI_LOGGER_FATAL("");
    }
    return output;
  }
  enum class Type {
    UNKNOWN,
    UNKNOWN_ERROR,
    MARKET_DATA_EVENTS,
    SUBSCRIPTION_STARTED,
    SUBSCRIPTION_FAILURE,
    SESSION_CONNECTION_UP,
    SESSION_CONNECTION_DOWN,
    SESSION_INCORRECT_STATES_FOUND
  };
  static std::string typeToString(Type type) {
    std::string output;
    switch (type) {
      case Type::UNKNOWN:
        output = "UNKNOWN";
        break;
      case Type::UNKNOWN_ERROR:
        output = "UNKNOWN_ERROR";
        break;
      case Type::MARKET_DATA_EVENTS:
        output = "MARKET_DATA_EVENTS";
        break;
      case Type::SUBSCRIPTION_STARTED:
        output = "SUBSCRIPTION_STARTED";
        break;
      case Type::SUBSCRIPTION_FAILURE:
        output = "SUBSCRIPTION_FAILURE";
        break;
      case Type::SESSION_CONNECTION_UP:
        output = "SESSION_CONNECTION_UP";
        break;
      case Type::SESSION_CONNECTION_DOWN:
        output = "SESSION_CONNECTION_DOWN";
        break;
      case Type::SESSION_INCORRECT_STATES_FOUND:
        output = "SESSION_INCORRECT_STATES_FOUND";
        break;
      default:
        CCAPI_LOGGER_FATAL("");
    }
    return output;
  }
  std::string toString() const {
    std::string output = "Message [type = " + typeToString(type) + ", recapType = " + recapTypeToString(recapType)
        + ", time = " + UtilTime::getISOTimestamp(time) + ", timeReceived = " + UtilTime::getISOTimestamp(timeReceived) + ", elementList = " + ccapi::firstNToString(elementList, 10)
        + ", correlationIdList = " + ccapi::toString(correlationIdList) + "]";
    return output;
  }
  const std::vector<Element>& getElementList() const {
    return elementList;
  }
  void setElementList(const std::vector<Element>& elementList) {
    this->elementList = elementList;
  }
  const std::vector<CorrelationId>& getCorrelationIdList() const {
    return correlationIdList;
  }
  void setCorrelationIdList(const std::vector<CorrelationId>& correlationIdList) {
    this->correlationIdList = correlationIdList;
  }
  TimePoint getTime() const {
    return time;
  }
  void setTime(TimePoint time) {
    this->time = time;
  }
  RecapType getRecapType() const {
    return recapType;
  }
  void setRecapType(RecapType recapType) {
    this->recapType = recapType;
  }
  Type getType() const {
    return type;
  }
  void setType(Type type) {
    this->type = type;
  }
  TimePoint getTimeReceived() const {
    return timeReceived;
  }
  void setTimeReceived(TimePoint timeReceived) {
    this->timeReceived = timeReceived;
  }

 private:
  TimePoint time{std::chrono::seconds{0}};
  TimePoint timeReceived{std::chrono::seconds{0}};
  std::vector<Element> elementList;
  std::vector<CorrelationId> correlationIdList;
  Type type{Type::UNKNOWN};
  RecapType recapType{RecapType::UNKNOWN};
};
} /* namespace ccapi */
#endif  // INCLUDE_CCAPI_CPP_CCAPI_MESSAGE_H_
