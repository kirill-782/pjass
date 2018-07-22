#include <stdint.h>
#include <stdio.h>

#include "blocks.h"
#include "misc.h"


static struct block_start {
    int lineno;
    enum block_type type;
    
};

static struct block_start *blocks = NULL;
static size_t size = 0;
static size_t capacity;

static char* names[] = { "function", "loop", "if" };


void block_push(int lineno, enum block_type type){
    if(! blocks){
        capacity = 7;
        blocks = malloc(sizeof(struct block_start) * capacity);
    }else if(size >= capacity){
        capacity *= 2;
        realloc(blocks, capacity * sizeof(struct block_start));
    }
    
    blocks[size].type = type;
    blocks[size].lineno = lineno;
    
    size++;
}

bool block_pop(enum block_type type, char *buf, size_t len){
    if(size == 0){
        // Standalone end* found
        snprintf(buf, len, "[1] Standalone %s (no corresponding opening block)", names[type]);
        return false;
    }

    
    if(blocks[size-1].type != type){
        // Missing end* for blocks[size-1].type
        snprintf(buf, len,  "[2] Missing end%s for block openend in line %d", names[blocks[size-1].type], blocks[size-1].lineno);
        return false;
    }
    
    size--;
    return true;
}


void block_missing_error(int x, char *msg, size_t len){
    if(size == 0){
        return;
    }
    snprintf(msg, len, "[%d] [3] Missing end%s for block opened in line %d.", x, names[blocks[size-1].type], blocks[size-1].lineno);
    size--;
}