#include "source/extensions/health_check/event_sinks/grpc/grpc_sink_impl.h"

#include "envoy/registry/registry.h"
#include "source/common/protobuf/utility.h"

namespace Envoy {
namespace Upstream {
void HealthCheckEventGrpcSink::log(
    envoy::data::core::v3::HealthCheckEvent event) {
    (void)event;
    printf("\033[0;32m[DEBUG] HealthCheckEventGrpcSink->log.\033[0m\n");
}

HealthCheckEventSinkPtr
HealthCheckEventGrpcSinkFactory::createHealthCheckEventSink(
    const ProtobufWkt::Any &config,
    Server::Configuration::HealthCheckerFactoryContext &context) {

    const auto &validator_config = Envoy::MessageUtil::anyConvert<
        envoy::extensions::health_check::event_sinks::grpc::v3::
            HealthCheckEventGrpcSink>(config);
    (void)config;
    (void)context;
    return std::make_unique<HealthCheckEventGrpcSink>(validator_config);
}

REGISTER_FACTORY(HealthCheckEventGrpcSinkFactory, HealthCheckEventSinkFactory);

} // namespace Upstream
} // namespace Envoy