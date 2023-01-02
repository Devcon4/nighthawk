CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

.PHONY: test clean watch glslc

nighthawk: src/**/*.cpp
		g++ $(CFLAGS) -g -o nighthawk src/main.cpp src/**/*.cpp $(LDFLAGS)

watch:
		while true; do inotifywait -qr -e modify -e create -e delete -e move ./src/**; echo "Files changed; rebuilding..."; make nighthawk; echo "Done!"; done

glslc: src/shaders/**
		$(foreach f,$^,glslc $(f) -o $(subst src/,bin/,$(subst .,_,$(f))).spv;)

test: nighthawk
		./nighthawk

clean:
		rm -f nighthawk