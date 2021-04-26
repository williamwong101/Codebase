"""Example TCP socket client."""
import socket
import json


def main(message_dict):
    """Test TCP Socket Client."""
    # create an INET, STREAMing socket, this is TCP
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # connect to the server
    sock.connect(("localhost", 8000))

    # send a message
    message = json.dumps(message_dict)
    sock.sendall(message.encode('utf-8'))
    sock.close()


if __name__ == "__main__":
    message_dict = {"hello": "world"}
    main(message_dict)