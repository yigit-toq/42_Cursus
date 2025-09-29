#!/bin/sh
# Start nginx in foreground (no loops). Config must be valid.
exec nginx -g 'daemon off;'
