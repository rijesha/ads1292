import java.awt.Container;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.io.IOException;
import java.io.InputStream;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

import org.apache.commons.cli.*;

import java.util.Random;

public class Serial_Main {
	private static Logger logger;
	private static boolean loggerStart;

	private static boolean disableGUI;
	private static String comPort = "COM9";
			
	private static InputStream in;
	private static byte[] dataPacket = new byte[10];
	private static int REALTIMEUPDATERATIO = 4;

	public static void main(String[] args) {
		parseCLI(args);
		logger = new Logger(loggerStart);

		SerialPortHandler s = new SerialPortHandler();	
		in = s.getSerialInputStream();

		try {
			Thread.sleep(200);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		try {
			s.connect(comPort);
			findHeaderStart();
			startSerialParsing();
		} catch (IOException | InterruptedException e) {
			System.out.println("Failed to Open Serial Port");
			e.printStackTrace();
			fakeData();
		}
		        
        
	}
	
	private static void parseCLI(String[] args) {
		Options options = new Options();

        Option input = new Option("c", "disable_gui", false, "disable the gui");
        options.addOption(input);

        Option output = new Option("l", "start_logging", false, "enabling logging on startup");
        options.addOption(output);

        Option serialport = new Option("d", "serial_device_port", false, "location of serial device port");
        options.addOption(serialport);

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

        disableGUI = cmd.hasOption("disable_gui");
		loggerStart = cmd.hasOption("start_logging");

		if (cmd.hasOption("serial_device_port"))
			comPort = cmd.getOptionValue("serial_device_port");
	}

	
	
	private static void findHeaderStart() throws IOException, InterruptedException{
		byte[] one = new byte[1]; 
		byte[] two = new byte[1];
		boolean foundStart = false;
		
		in.read(one);
		while (foundStart == false){
			one = two;
			in.read(two);
			Thread.sleep(2);
			if ((one[0] == 21) && (two[0] == 22))
				foundStart = true;
		}
	}
	
	private static void startSerialParsing() throws IOException, InterruptedException{
		int realTimeUpdateCounter = 0;
		
		while (true){
			if (in.available() > 10){
				in.read(dataPacket);
				if (dataPacket[0] == 19 && dataPacket[1] == 20 && dataPacket[8] == 21 && dataPacket[9] == 22 ){
					int chan1 = dataPacket[2] << 16 | (dataPacket[3] & 0xff) << 8 | (dataPacket[4] & 0xff);
					int chan2 = dataPacket[5] << 16 | (dataPacket[6] & 0xff) << 8 | (dataPacket[7] & 0xff);

					String data = String.valueOf(System.currentTimeMillis()) + " " +  chan1 + " " + chan2;
					
					if (loggerStart)
						logger.writeLine(data);

					System.out.println(data);
				}
				else
					findHeaderStart();
			}
			Thread.sleep(1);
		}
	}

	private static void fakeData() {
		int realTimeUpdateCounter = 0;
		Random rn = new Random();

		while (true){
			int chan1 = rn.nextInt();
			int chan2 = rn.nextInt();

			String data = String.valueOf(System.currentTimeMillis()) + " " +  chan1 + " " + chan2;
					
			if (loggerStart)
				logger.writeLine(data);
			
			System.out.println(data);

			try {
				Thread.sleep(8);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}

}
