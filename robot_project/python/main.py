from cvzone.HandTrackingModule import HandDetector
import cv2
import serial
import serial.tools.list_ports
import time
import socket

host = '192.168.204.78'  # '192.168.1.100' # Replace with Arduino's IP address
port = 80

ser = None
s = None


# Function to send command to Arduino
def send_command(data_to_send):
    global s
    print("Connected!")
    # s.sendall(data_to_send.encode())

    s.sendall(data_to_send.encode())
    # time.sleep(0.5)

    print("Data sent!: ", data_to_send)

    # global ser
    # ser.write(command.encode())  # Send command to Arduino
    # print(f"Sent command: {command}")


def run():
    global s
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))

    # global ser
    # for port in ports:
    #     print(port.device)
    #     print(port[0][:4])

    # Configure serial port
    # ser = serial.Serial('COM8', 9600, timeout=1)
    # time.sleep(5)  # Wait for serial port to initialize

    detector = HandDetector(detectionCon=0.8, maxHands=1)   # Initialize hand detector
    cap = cv2.VideoCapture(0)   # Open webcam
    previous_time = time.time()

    while True:
        # Read frame from webcam
        success, frame = cap.read()
        if not success:
            break

        hands, frame = detector.findHands(frame)  # Detect hands in the frame

        if hands is not None and len(hands) > 0:
            hand = hands[0]
            fingers = detector.fingersUp(hand)
            fingers_count = sum(fingers)
            if time.time() - previous_time >= 0.5:
                print("Send command")
                if fingers_count == 0:
                    print("Go!")
                    send_command('F')  # Move forward
                    # send_command('S')  # STOP
                elif fingers_count == 5:
                    send_command('S')  # STOP
                    print("Unknown, STOP")
                else:
                    send_command('B')  # STOP
                    print("Backward!")
                previous_time = time.time()
        else:
            print("No hands PANIC!")

        cv2.imshow("Hand Tracking", frame)

        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release the webcam and close the window
    cap.release()
    cv2.destroyAllWindows()

    # Close serial port
    # ser.close()
    s.close()


if __name__ == '__main__':
    ports = serial.tools.list_ports.comports()
    print(ports)

    # if len(ports) > 0:
    run()

