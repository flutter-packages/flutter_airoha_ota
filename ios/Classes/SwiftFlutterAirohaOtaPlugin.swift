import Flutter
import UIKit


import Airoha1562

public class SwiftFlutterAirohaOtaPlugin: NSObject, FlutterPlugin, AirohaConnectionListener {
    
    public func onStatusChanged(status: Int) {
        if status == AirohaConnectStatus.connected.rawValue {
            print("onStatusChanged connected")
            // ota进度方法调用
            SwiftFlutterAirohaOtaPlugin.otaChannel?.invokeMethod("progress", arguments: 100)
        }
        else if status == AirohaConnectStatus.onInitialized.rawValue {
            print("onStatusChanged onInitialized")
        }
        else if status == AirohaConnectStatus.disconnected.rawValue {
            print("onStatusChanged disconnected")
        }
        else if status == AirohaConnectStatus.initializationFail.rawValue {
            print("onStatusChanged initializationFail")
        }
    }
    
    public func onDataReceived(deviceMessage: AirohaBaseMsg) {
        print("onDataReceived",separator: deviceMessage.getMsgContent().description)
    }
    
  static var otaChannel : FlutterMethodChannel?
    
  public static func register(with registrar: FlutterPluginRegistrar) {
    otaChannel = FlutterMethodChannel(name: "flutter_airoha_ota", binaryMessenger: registrar.messenger())
    let instance = SwiftFlutterAirohaOtaPlugin()
    registrar.addMethodCallDelegate(instance, channel: otaChannel!)
  }

  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
    if(call.method == "startFota"){
        let arguments : [String] = call.arguments as! [String]
        let deviceId = arguments[0]
        let leftFilePath = arguments[1]
        let rightFilePath = arguments[2]
        let device = AirohaDevice()
        device.setPeripheralID(UUID(uuidString: deviceId)!)
        print("deviceId"+String(deviceId))
        // 升级包路径 L & R
        print("leftFilePath"+String(leftFilePath))
        print("rightFilePath"+String(rightFilePath))
        AirohaSdkMgr.Inst.getAirohaConnector().connect(device: device, connectionListener: self)
    }
  }
}
