run : main.c  clean main
	gcc -Wall -Werror -Wextra -Ofast $< -o $@
	./main
	

udp_server: udp_server.c 
	gcc -Wall -Werror -Wextra -Ofast $< -o $@
	./udp_server
	
udp_client : udp_client.c
	gcc -Wall -Werror -Wextra -Ofast $< -o $@
	./udp_client

tcp_client : tcp_client.c clean tcp_client 
	gcc -Wall -Werror -Wextra -Ofast $< -o $@
	./tcp_client

tcp_server: tcp_server.c
	gcc -Wall -Werror -Wextra -Ofast $< -o $@
	./tcp_server

clean:
	rm -f tcp_client
	rm -f tcp_server
	rm -f udp_client
	rm -f udp_server
	rm -f main


