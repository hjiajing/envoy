#pragma once

#include "envoy/access_log/access_log.h"
#include "envoy/extensions/health_check/event_sinks/grpc/v3/grpc.pb.h"
#include "envoy/upstream/health_check_event_sink.h"
#include "source/common/protobuf/utility.h"

namespace Envoy {
namespace Upstream {
class HealthCheckEventGrpcSink : public HealthCheckEventSink {
  public:
    explicit HealthCheckEventGrpcSink() {
        printf("\033[0;32m[DEBUG] HealthCheckEventGrpcSink c'tor.\033[0m\n");
    }

    explicit HealthCheckEventGrpcSink(
        const envoy::extensions::health_check::event_sinks::grpc::v3::
            HealthCheckEventGrpcSink &config) {
        printf("\033[0;32m[DEBUG] HealthCheckEventGrpcSink c'tor with "
               "config.\033[0m\n");
        printf("config is %s\n", config.DebugString().c_str());
        (void)config;
    }
    void log(envoy::data::core::v3::HealthCheckEvent event) override;
};

class HealthCheckEventGrpcSinkFactory : public HealthCheckEventSinkFactory {
  public:
    HealthCheckEventGrpcSinkFactory() = default;

    std::string name() const override {
        return "envoy.health_check_event_sink.grpc";
    }

    HealthCheckEventSinkPtr createHealthCheckEventSink(
        const ProtobufWkt::Any &config,
        Server::Configuration::HealthCheckerFactoryContext &context) override;

    ProtobufTypes::MessagePtr createEmptyConfigProto() override {
        return ProtobufTypes::MessagePtr{
            new envoy::extensions::health_check::event_sinks::grpc::v3::
                HealthCheckEventGrpcSink()};
    }
};

template <class Context>
class HealthCheckGrpcInstanceFactoryBase : public Config::TypedFactory {
  public:
    HealthCheckGrpcInstanceFactoryBase() : category_(categoryByType()) {}

    ~HealthCheckGrpcInstanceFactoryBase() override = default;

    virtual AccessLog::InstanceBaseSharedPtr<Context>
    createHealthCheckGrpcInstance(
        const Protobuf::Message &config,
        Server::Configuration::FactoryContext &context) PURE;
    std::string category() const override { return category_; }

  private:
    std::string categoryByType() {
        return "envoy.health_check_event_sink.grpc";
    }
    const std::string category_;
};

using HealthCheckGrpcInstanceFactory =
    HealthCheckGrpcInstanceFactoryBase<Formatter::HttpFormatterContext>;

} // namespace Upstream
} // namespace Envoy