#include <stdio.h>
#include <stdlib.h>

// Function to reverse the contents of a file
void rcat(const char *filename) {
	FILE *file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Failed to open file");
		return;
	}

	// Move to the end of the file
	if (fseek(file, 0, SEEK_END) != 0) {
		perror("Failed to seek to end of file");
		fclose(file);
		return;
	}

	// Get the size of the file
	long file_size = ftell(file);
	if (file_size == -1) {
		perror("Failed to get file size");
		fclose(file);
		return;
	}

	// Allocate a buffer to hold the file contents
	char *buffer = (char *)malloc(file_size);
	if (buffer == NULL) {
		perror("Failed to allocate memory");
		fclose(file);
		return;
	}

	// Read the file into the buffer
	if (fseek(file, 0, SEEK_SET) != 0) {
		perror("Failed to seek to start of file");
		free(buffer);
		fclose(file);
		return;
	}
	if (fread(buffer, 1, file_size, file) != file_size) {
		perror("Failed to read file");
		free(buffer);
		fclose(file);
		return;
	}

	// Print the file contents in reverse order
	for (long i = file_size - 1; i >= 0; i--) {
		putchar(buffer[i]);
	}

	// Clean up
	free(buffer);
	fclose(file);
}

// Main function to demonstrate rcat
int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}

	rcat(argv[1]);

	return EXIT_SUCCESS;
}

