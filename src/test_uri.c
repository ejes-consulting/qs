#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "uri.h"

void test_encodeURIComponent() {
    char *encoded;
    
    // Basic cases
    encoded = encodeURIComponent("Hello, World!", 13);
    assert(strcmp(encoded, "Hello%2C%20World!") == 0);
    free(encoded);
    
    encoded = encodeURIComponent("space test", 10);
    assert(strcmp(encoded, "space%20test") == 0);
    free(encoded);
    
    // Reserved characters
    encoded = encodeURIComponent("#$&+,/:;=?@", 16);
    assert(strcmp(encoded, "%23%24%26%2B%2C%2F%3A%3B%3D%3F%40") == 0);
    free(encoded);
    
    // Alphanumeric characters should remain unchanged
    encoded = encodeURIComponent("ABCabc123", 9);
    assert(strcmp(encoded, "ABCabc123") == 0);
    free(encoded);
    
    // RFC compliance mode
    rfc_compliant = true;
    encoded = encodeURIComponent("!'()*", 6);
    assert(strcmp(encoded, "%21%27%28%29%2A") == 0);
    free(encoded);
    rfc_compliant = false;

    // Edge cases
    encoded = encodeURIComponent("", 0);
    assert(encoded == NULL);
    
    encoded = encodeURIComponent("A", 1);
    assert(strcmp(encoded, "A") == 0);
    free(encoded);
}

void test_decodeURIComponent() {
    char *decoded;
    
    // Basic cases
    decoded = decodeURIComponent("Hello%2C%20World%21", 19);
    assert(strcmp(decoded, "Hello, World!") == 0);
    free(decoded);
    
    decoded = decodeURIComponent("space%20test", 12);
    assert(strcmp(decoded, "space test") == 0);
    free(decoded);
    
    // Reserved characters
    decoded = decodeURIComponent("%21%23%24%26%27%28%29%2A%2B", 24);
    assert(strcmp(decoded, "!#$&'()*") == 0);
    free(decoded);
    
    // Mixed valid and invalid encoding
    decoded = decodeURIComponent("%41%42%43invalid%20%25%47", 23);
    assert(strcmp(decoded, "ABCinvalid %%") == 0);
    free(decoded);
    
    // Edge cases
    decoded = decodeURIComponent("", 0);
    assert(strcmp(decoded,"")==0);
    
    decoded = decodeURIComponent("%20", 3);
    assert(strcmp(decoded, " ") == 0);
    free(decoded);
}

int main() {
    test_encodeURIComponent();
    test_decodeURIComponent();
    printf("All tests passed!\n");
    return 0;
}
