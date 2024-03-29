CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

.PHONY: test clean watch glslc resources

nighthawk: src/**/*.cpp
		g++ $(CFLAGS) -g -o bin/nighthawk src/main.cpp src/**/*.cpp -I lib $(LDFLAGS)

watch:
		while true; do inotifywait -qr -e modify -e create -e delete -e move ./src/**; echo "Files changed; rebuilding..."; make nighthawk; echo "Done!"; done

glslc: src/shaders/**
		mkdir -p bin/shaders
		$(foreach f,$^,glslc $(f) -o $(subst src/,bin/,$(subst .,_,$(f))).spv;)

resources: glslc
		mkdir -p bin/textures
		cp -r src/textures/ bin/
		mkdir -p bin/resources
		cp -r src/resources bin/

test: bin/nighthawk
		./bin/nighthawk

clean:
		rm -f bin/