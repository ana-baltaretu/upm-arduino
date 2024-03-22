from cvzone.HandTrackingModule import HandDetector
import cv2
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
    s.sendall(data_to_send.encode())
    print("Data sent!: ", data_to_send)


def run():
    global s
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, port))

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
            if time.time() - previous_time >= 0.4:
                if fingers_count <= 1:  # Move forward
                    print("Send command: GO!")
                    send_command('F')
                elif fingers_count == 2:  # Move backward
                    print("Send command: BACK!")
                    send_command('B')
                elif fingers_count == 3:  # Rotate left
                    print("Send command: LEFT!")
                    send_command('L')
                elif fingers_count == 4:  # Rotate right
                    print("Send command: RIGHT!")
                    send_command('R')
                elif fingers_count == 5: # STOP
                    send_command('S')
                    print("Send command: STOP!")
                else:   # ANYTHING ELSE => CONFUSION => STOP!!!!!!
                    print("Unknown, STOP")
                    send_command('S')  # STOP
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

    # Close socket
    s.close()


if __name__ == '__main__':
    run()

