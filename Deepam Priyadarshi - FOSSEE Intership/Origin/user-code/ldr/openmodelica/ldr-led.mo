model ldr_led "LED indicating light sensor readings"
  extends Modelica.Icons.Example;
  import sComm = Arduino.SerialCommunication.Functions;
  import strm = Modelica.Utilities.Streams;
  Integer ok(fixed = false);
  Integer val(fixed = false);
  Integer digital_out(fixed = false);
  Integer c_ok(fixed = false);
algorithm
  when initial() then
    ok := sComm.open_serial(1, 2, 115200) "At port 2 with baudrate of 115200";
    sComm.delay(2000);
  end when;
  if ok <> 0 then
    strm.print("Unable to open serial port, please check");
  else
    val := sComm.cmd_analog_in(1, 5) "read analog pin 5 (ldr)";
    strm.print("LDR Readings: " + String(val));
    if val < 300 then
      digital_out := sComm.cmd_digital_out(1, 11, 1) "Turn ON LED";
    else
      digital_out := sComm.cmd_digital_out(1, 11, 0) "Turn OFF LED";
    end if;
    sComm.delay(500);
  end if;
//strm.print(String(time));
  when time >= 10 then
    c_ok := sComm.close_serial(1) "To close the connection safely";
  end when;
//Setting Threshold value of 300
  annotation(
    experiment(StartTime = 0, StopTime = 10, Tolerance = 1e-6, Interval = 0.2));
end ldr_led;
