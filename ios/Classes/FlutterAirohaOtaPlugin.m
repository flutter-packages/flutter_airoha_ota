#import "FlutterAirohaOtaPlugin.h"
#if __has_include(<flutter_airoha_ota/flutter_airoha_ota-Swift.h>)
#import <flutter_airoha_ota/flutter_airoha_ota-Swift.h>
#else
// Support project import fallback if the generated compatibility header
// is not copied when this plugin is created as a library.
// https://forums.swift.org/t/swift-static-libraries-dont-copy-generated-objective-c-header/19816
#import "flutter_airoha_ota-Swift.h"
#endif

@implementation FlutterAirohaOtaPlugin
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  [SwiftFlutterAirohaOtaPlugin registerWithRegistrar:registrar];
}
@end
