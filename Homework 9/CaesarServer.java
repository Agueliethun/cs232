import java.net.*;
import java.io.*;
import java.util.*;
import java.text.DateFormat;
import java.text.SimpleDateFormat;

public class CaesarServer implements Runnable {
	// ServerSocket server;
	String line;
	BufferedReader input;
	DataOutputStream output;
	Socket client;
	SimpleDateFormat format;

	// Constructor for our server which just stores the socket info
	public CaesarServer (Socket socket) {
		this.client = socket;
		format = new SimpleDateFormat("yyyy.MM.dd G ';'  HH:mm:ss z");
	}

	// Defines the thread behavior
	public void run() {
		try {
			// Display info on the client and date/time
			Date currentDate = new Date();
			System.out.println("Client Connected: ");
			System.out.println("Time: " + format.format(currentDate));
			System.out.println("IP: " + client.getInetAddress());

			input = new BufferedReader( new InputStreamReader( client.getInputStream()));
			output = new DataOutputStream( client.getOutputStream());

			// Read in the first thing, which must be a number between 1 and 25
			line = input.readLine();

			// Make sure our rotation value is valid
			int rotation = Integer.parseInt(line);
			if (rotation < 1 || rotation > 25) {
				output.writeBytes("Bad rotation #: must be integer between 1 and 25 inclusive.\n");
				System.out.println("Bad rotation, exiting...");

				// Close the connection and exit
				input.close();
				output.close();
				client.close();

				Thread.currentThread().interrupt();
			} else {
				output.writeBytes(rotation + "\n");
			}

			line = input.readLine();
			// Now continue reading in strings and rotating them until we hear "quit"
			while (line != null && line.indexOf("quit") == -1) {
				String responseLine = "";
				System.out.println("Received string: " + line);

				for (int i = 0; i < line.length(); i++) {
					char currentChar = line.charAt(i);
					if (currentChar >= 'A' && currentChar <= 'Z') {
						currentChar = (char)((currentChar + rotation - 'A') % ('Z' - 'A' + 1) + 'A');
					} else if (currentChar >= 'a' && currentChar <= 'z') {
						currentChar = (char)((currentChar + rotation - 'a') % ('z' - 'a' + 1) + 'a');
					}
					responseLine += currentChar;
				}

				// Write out the response to the client and read in new line
				output.writeBytes(responseLine + "\n");
				line = input.readLine();
			}

			// Close the connection and exit
			input.close();
			output.close();
			client.close();

			Thread.currentThread().interrupt();
		}
		catch (IOException e) {
			System.err.println(e);
		}
	}

	// Defines the behavior of our main thread
	public static void main(String[] args) throws IOException {
		String line = "";
		BufferedReader input = null;
		DataOutputStream output = null;
		Socket client = null;

		System.out.println("Welcome to the mrn6 Caesar Cipher Server!");

		// Make sure arguments are all present
		if (args.length < 1) {
			System.err.println("Invalid number of arguments. Proper syntax: java CaesarServer [port]");
			System.exit(-1);
		}

		// Grab the info from our arguments
		int port = Integer.parseInt(args[0]);

		// Create our server
		ServerSocket server = new ServerSocket(port);
		System.out.println("Server Socket Created");

		// Continue looping forever and accept new connections
		while (true) {
			try {
				client = server.accept();

				Thread serverThread = new Thread( new CaesarServer( client ));
				serverThread.start();
			}
			catch (IOException e) {
				System.err.println(e);
			}
		}
	}
}
