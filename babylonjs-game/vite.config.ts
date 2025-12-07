import { defineConfig } from 'vite';
import { resolve } from 'path';

export default defineConfig({
  resolve: {
    alias: {
      '@engine': resolve(__dirname, './src/engine'),
      '@game': resolve(__dirname, './src/game'),
      '@ui': resolve(__dirname, './src/ui'),
      '@types': resolve(__dirname, './src/types'),
    },
  },
  build: {
    lib: {
      entry: resolve(__dirname, 'src/index.ts'),
      name: 'GameEngine',
      fileName: 'index',
      formats: ['es'],
    },
    rollupOptions: {
      external: ['@babylonjs/core', '@babylonjs/havok', '@babylonjs/loaders'],
    },
  },
  server: {
    port: 3000,
    open: true,
  },
});
