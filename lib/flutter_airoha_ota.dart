import 'dart:async';

import 'package:flutter/rendering.dart';
import 'package:flutter/services.dart';

class FlutterAirohaOta {
  static const MethodChannel _channel = const MethodChannel('flutter_airoha_ota');
  final StreamController<MethodCall> _methodStreamController = new StreamController.broadcast(); // ignore: close_sinks
  Stream<MethodCall> get _methodStream => _methodStreamController.stream;

  static FlutterAirohaOta _instance = new FlutterAirohaOta._();

  static FlutterAirohaOta get instance => _instance;


  static FlutterAirohaOta getInstance() {
    if (_instance == null) {
      _instance = FlutterAirohaOta._();
    }
    return _instance;
  }

  FlutterAirohaOta._() {
    _channel.setMethodCallHandler((MethodCall call) {
      _methodStreamController.add(call);
    });
  }

  Future<void> startFota(String deviceId,String leftFilePath, String rightFilePath, ) {
    return _channel.invokeMethod('startFota', [deviceId,leftFilePath, rightFilePath]);
  }

  progress(Function progress) async {
    return FlutterAirohaOta.instance._methodStream.where((m) => m.method == "progress").map((m) => m.arguments).listen(progress);
  }
}
