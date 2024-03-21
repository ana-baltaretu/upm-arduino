from cvzone.HandTrackingModule import HandDetector
import cv2

if __name__ == '__main__':
    detector = HandDetector(detectionCon=0.8, maxHands=1)   # Initialize hand detector
    cap = cv2.VideoCapture(0)   # Open webcam

    while True:
        # Read frame from webcam
        success, frame = cap.read()
        if not success:
            break

        hands, frame = detector.findHands(frame)  # Detect hands in the frame

        if hands is not None and len(hands) > 0:
            # cv2.imshow("Hand Tracking", frame)
            hand = hands[0]
            fingers = detector.fingersUp(hand)
            fingers_count = sum(fingers)
            if fingers_count == 0:
                print("Go!")
            elif fingers_count == 5:
                print("Stop!")
            else:
                print("Unknown")

            # print(fingers)
        else:
            print("No hands")
        cv2.imshow("Hand Tracking", frame)

        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release the webcam and close the window
    cap.release()
    cv2.destroyAllWindows()
