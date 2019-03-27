// import java.net.Socket, java.io.IOException, java.net.SocketException, java.net.UnknownHostException, java.io.DataOutputStream, java.io.BufferedReader, java.io.InputStreamReader;
import java.net.*;
import java.io.*;
import java.util.*;

public class CaesarClient {

	public static void main(String[] args) {
		Socket caesarSocket = null;
		DataOutputStream output = null;
		BufferedReader input = null;

		BufferedReader userbr = new BufferedReader(new InputStreamReader(System.in));

		Scanner s = new Scanner(System.in);

		System.out.println("Welcome to the mrn6 Caesar Cipher Client!");
		
		// Make sure arguments are all present
		if (args.length < 2) {
			System.err.println("Invalid number of arguments. Proper syntax: java CaesarClient [hostname] [port]");
			System.exit(-1);
		}
		
		// Grab the info from our arguments
		String hostname = args[0];
		int port = Integer.parseInt(args[1]);

		// Get rotation amount
		System.out.print("Please enter the rotation amount (1..25): \t");
		int rotation = s.nextInt();

		// Attempt to create the socket and streams
		try {
			// Create the socket
			caesarSocket = new Socket(hostname, port);
			// caesarSocket = new Socket("brooks.cs.calvin.edu", 9876);
			output = new DataOutputStream(caesarSocket.getOutputStream());
			input = new BufferedReader( new InputStreamReader( caesarSocket.getInputStream()) );
		} 
		catch (IOException e) {
			System.err.println(e);
		}

		String responseLine;
		// If everything works, continue and print out the rotation to the server
		if (caesarSocket != null && input != null && output != null) {
			try {
				// Write out the rotation to the server
				output.writeBytes(Integer.toString(rotation) + "\n");
				// Read in the response
				responseLine = input.readLine();

				// If we receive a response from the server that is bad, exit
				if (responseLine.indexOf("Bad rotation #")!=-1) {
					System.out.println("Connection closed, exiting...");
					output.close();
					input.close();
					caesarSocket.close();
					System.exit(-1);
				}

				// Now, begin prompting the user for lines to be rotated
				System.out.print("Please enter text to be rotated:\t");
				String line = userbr.readLine();

				String rotatedLine = "";
				while (line.indexOf("quit")==-1) {
					output.writeBytes(line + "\n");
					rotatedLine = input.readLine();
					System.out.println("Server's rotated text:\t" + rotatedLine);

					System.out.print("Please enter text to be rotated:\t");
					line = userbr.readLine();
				}

				// Exit the thread since we are done
				output.close();
				input.close();
				caesarSocket.close();
				System.exit(0);
			}
			catch (IOException e) {
				System.err.println(e);
			}
		}		
	}	
}
