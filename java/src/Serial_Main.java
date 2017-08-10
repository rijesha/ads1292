import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import org.apache.commons.cli.*;

import java.util.Arrays;
import java.util.Random;

public class Serial_Main {
	private static Logger logger;
	private static boolean loggerStart;

	private static boolean verbose;
	private static boolean fakeDataEnabled;
	private static String comPort = "COM3";
			
	private static InputStream in;
	private static byte[] radarPacket = new byte[8];

	private static byte[] gpsVelPacket = new byte[14];
	private static byte[] gpsPosPacket = new byte[18];

	
	public static void main(String[] args) {
		parseCLI(args);
		logger = new Logger(loggerStart);

		SerialPortHandler s = new SerialPortHandler();	

		try {
			Thread.sleep(200);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		try {
			System.out.println(comPort);
			s.connect(comPort);
			in = s.getSerialInputStream();
			findHeaderStart();
			startSerialParsing();
		} catch (IOException | InterruptedException e) {
			System.out.println("Failed to Open Serial Port");
			e.printStackTrace();
			if (fakeDataEnabled)
				fakeData();
		}
		        
        
	}
	
	private static void parseCLI(String[] args) {
		Options options = new Options();

        //Option input = new Option("c", "disable_gui", false, "disable the gui");
        //options.addOption(input);

        Option output = new Option("l", "start_logging", false, "enabling logging on startup");
        options.addOption(output);

        Option serialport = new Option("d", "serial_device_port", true, "location of serial device port");
        options.addOption(serialport);

        Option verboseOption = new Option("v", "quiet", false, "disables write of values to std_out");
        options.addOption(verboseOption);

        Option fakeDataEnabledOption = new Option("f", "fake_data", false, "Use Fake Data on Seial Failure");
        options.addOption(fakeDataEnabledOption);

        CommandLineParser parser = new DefaultParser();
        HelpFormatter formatter = new HelpFormatter();
        CommandLine cmd;

        try {
            cmd = parser.parse(options, args);
        } catch (ParseException e) {
            System.out.println(e.getMessage());
            formatter.printHelp("Real Time FFT Grapher", options);

            System.exit(1);
            return;
        }

		loggerStart = cmd.hasOption("start_logging");

		verbose = !cmd.hasOption("quiet");
		fakeDataEnabled = cmd.hasOption("fake_data");

		if (cmd.hasOption("serial_device_port")){
			comPort = cmd.getOptionValue("serial_device_port");
		}
			
	}
	
	private static void findHeaderStart() throws IOException, InterruptedException{
		byte[] one = new byte[1]; 
		byte[] two = new byte[1];
		System.out.println("FINDING HEADER START");
		boolean foundStart = false;
		
		in.read(one);
		while (foundStart == false){
			one[0] = two[0];
			in.read(two);
			Thread.sleep(2);
			if ((one[0] == 19) && (two[0] == 20))
				foundStart = true;
		}
	}
	
	private static void startSerialParsing() throws IOException, InterruptedException{
		int packetSize = 0;
		String data = "null";
		ByteBuffer bb = ByteBuffer.allocate(4);
		byte[] tempVar = new byte[4];
		
		while (true){
			if (in.available() > 1) {
				packetSize = in.read();
			
			while (in.available() < packetSize + 2) {
				Thread.sleep(1);
			}
			
			switch (packetSize) {
            	case 6:  
            		in.read(radarPacket);
            		if (radarPacket[6] == 19 && radarPacket[7] == 20 ){
    					int chan1 = radarPacket[0] << 16 | (radarPacket[1] & 0xff) << 8 | (radarPacket[2] & 0xff);
    					int chan2 = radarPacket[3] << 16 | (radarPacket[4] & 0xff) << 8 | (radarPacket[5] & 0xff);
    					data = String.valueOf(System.currentTimeMillis()) + " " +  chan1 + " " + chan2;   					
    				}
    				else
    					findHeaderStart();
            		break;
            
            	case 4:
            		int test = readInteger();
            		
            		if (in.read() == 19 && in.read() == 20) {
            			data = String.valueOf(System.currentTimeMillis()) + " " +  test;   					
    				}
            		else
            			findHeaderStart();
            		
            		break;
            		
            	case 12:
            		long gspeed = intToUnsigned(readInteger());
            		int z_dot = readInteger();
            		int heading = readInteger();
            		
            		if (in.read() == 19 && in.read() == 20) {
            			data = String.valueOf(System.currentTimeMillis()) + " " +  gspeed + " " + z_dot + " " + heading;   					
    				}
            		else
            			findHeaderStart();
            		
            		break;
            	
            	case 16:
            		int lon = readInteger();
            		int lat = readInteger();
            		int hMSL = readInteger();
            		long hAcc = intToUnsigned(readInteger());
            		
            		if (in.read() == 19 && in.read() == 20) {
            			data = String.valueOf(System.currentTimeMillis()) + " " +  lon + " " + lat + " " + hMSL + " " + hAcc;   					
    				}
            		else
            			findHeaderStart();
            		
            		break;
            	
            	default: findHeaderStart();
            		break;
			}
			
			if (loggerStart)
				logger.writeLine(data);

			if (verbose)
				System.out.println(data);
			
			}
			
			Thread.sleep(1);
		}
	}

	private static int readInteger() throws IOException {
		byte[] tempVar = new byte[4];
		in.read(tempVar);
		ByteBuffer bb = ByteBuffer.wrap(tempVar);
		bb.order(ByteOrder.LITTLE_ENDIAN);
		return bb.getInt();
	}
	
	private static long intToUnsigned(int num) {
		return num & 0x00000000ffffffffL;
	}
	
	private static void fakeData() {
		Random rn = new Random();

		while (true){
			int chan1 = rn.nextInt();
			int chan2 = rn.nextInt();

			String data = String.valueOf(System.currentTimeMillis()) + " " +  chan1 + " " + chan2;
					
			if (loggerStart)
				logger.writeLine(data);
			
			if (verbose)
				System.out.println(data);

			try {
				Thread.sleep(8);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

}

