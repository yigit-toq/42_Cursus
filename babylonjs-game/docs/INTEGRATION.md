# Entegrasyon Rehberi

Bu doküman, Game Engine'in frontend projenize nasıl entegre edileceğini açıklar.

## 📦 Kurulum Seçenekleri

### Seçenek 1: Monorepo Yapısı (Önerilen)

```
ft_transcendence/
├── backend/              # Fastify API
├── frontend/             # React/Vue/Vanilla TS
└── game-engine/          # Bu proje (babylonjs-game)
```

**Avantajlar:**
- Tek bir repository, kolay yönetim
- Shared types kullanabilirsiniz
- Tek build sistemi

### Seçenek 2: Separate Package

Game engine'i ayrı bir npm package olarak publish edin ve frontend'de kullanın.

```bash
cd babylonjs-game
npm run build
npm link

cd ../frontend
npm link @ft-transcendence/game-engine
```

## 🔌 Frontend'e Entegrasyon

### Vanilla TypeScript

```typescript
// main.ts
import { GameEngine, SceneManager } from '@ft-transcendence/game-engine';

const engine = new GameEngine({
  canvasId: 'gameCanvas',
  antialias: true,
});

const sceneManager = new SceneManager(engine);
sceneManager.setupDefaultCamera();
sceneManager.setupDefaultLighting();

engine.setScene(sceneManager.getScene());
engine.start();
```

### React Entegrasyonu

```tsx
// GameCanvas.tsx
import { useEffect, useRef } from 'react';
import { GameEngine, SceneManager } from '@ft-transcendence/game-engine';

export const GameCanvas: React.FC = () => {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const engineRef = useRef<GameEngine | null>(null);

  useEffect(() => {
    if (!canvasRef.current) return;

    const engine = new GameEngine({
      canvasId: 'gameCanvas',
      antialias: true,
    });

    const sceneManager = new SceneManager(engine);
    sceneManager.setupDefaultCamera();
    sceneManager.setupDefaultLighting();

    engine.setScene(sceneManager.getScene());
    engine.start();

    engineRef.current = engine;

    return () => {
      engine.dispose();
    };
  }, []);

  return (
    <canvas 
      id="gameCanvas" 
      ref={canvasRef}
      style={{ width: '100%', height: '100vh' }}
    />
  );
};
```

### Vue Entegrasyonu

```vue
<!-- GameCanvas.vue -->
<template>
  <canvas id="gameCanvas" ref="canvasRef"></canvas>
</template>

<script setup lang="ts">
import { onMounted, onUnmounted, ref } from 'vue';
import { GameEngine, SceneManager } from '@ft-transcendence/game-engine';

const canvasRef = ref<HTMLCanvasElement>();
let engine: GameEngine | null = null;

onMounted(() => {
  engine = new GameEngine({
    canvasId: 'gameCanvas',
    antialias: true,
  });

  const sceneManager = new SceneManager(engine);
  sceneManager.setupDefaultCamera();
  sceneManager.setupDefaultLighting();

  engine.setScene(sceneManager.getScene());
  engine.start();
});

onUnmounted(() => {
  engine?.dispose();
});
</script>

<style scoped>
canvas {
  width: 100%;
  height: 100vh;
}
</style>
```

## 🔄 Backend ile İletişim

### WebSocket Entegrasyonu

```typescript
// gameClient.ts
import { GameEngine, SceneManager } from '@ft-transcendence/game-engine';

class GameClient {
  private engine: GameEngine;
  private ws: WebSocket;

  constructor(wsUrl: string) {
    this.engine = new GameEngine({
      canvasId: 'gameCanvas',
      antialias: true,
    });

    // WebSocket bağlantısı
    this.ws = new WebSocket(wsUrl);
    
    this.ws.onmessage = (event) => {
      const data = JSON.parse(event.data);
      this.handleGameState(data);
    };

    this.setupGame();
  }

  private setupGame() {
    const sceneManager = new SceneManager(this.engine);
    sceneManager.setupDefaultCamera();
    sceneManager.setupDefaultLighting();

    this.engine.setScene(sceneManager.getScene());
    this.engine.start();
  }

  private handleGameState(state: any) {
    // Backend'den gelen oyun state'ini uygula
    console.log('Game state updated:', state);
  }

  public sendInput(input: any) {
    this.ws.send(JSON.stringify({ type: 'input', data: input }));
  }
}

export default GameClient;
```

### REST API Entegrasyonu

```typescript
// gameApi.ts
export class GameAPI {
  private baseUrl: string;

  constructor(baseUrl: string = 'http://localhost:3001') {
    this.baseUrl = baseUrl;
  }

  async createGame(): Promise<{ gameId: string }> {
    const response = await fetch(`${this.baseUrl}/api/games`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
    });
    return response.json();
  }

  async joinGame(gameId: string): Promise<void> {
    await fetch(`${this.baseUrl}/api/games/${gameId}/join`, {
      method: 'POST',
    });
  }

  async getGameState(gameId: string): Promise<any> {
    const response = await fetch(`${this.baseUrl}/api/games/${gameId}`);
    return response.json();
  }
}
```

## 🎮 Oyun Geliştirme Akışı

### 1. Engine'i Başlat
```typescript
const engine = new GameEngine({ canvasId: 'gameCanvas' });
```

### 2. Sahne Oluştur
```typescript
const sceneManager = new SceneManager(engine);
sceneManager.setupDefaultCamera();
sceneManager.setupDefaultLighting();
```

### 3. Oyun Objelerini Ekle
```typescript
// Gelecekte: Issue #7 - PongGame implementasyonu
// const pongGame = new PongGame(sceneManager);
```

### 4. Backend'e Bağlan
```typescript
const ws = new WebSocket('ws://localhost:3001/game');
ws.onmessage = (event) => {
  // State güncellemelerini al
};
```

### 5. Oyunu Başlat
```typescript
engine.setScene(sceneManager.getScene());
engine.start();
```

## 📁 Dosya Yapısı (Entegre Edilmiş)

```
ft_transcendence/
├── backend/
│   ├── src/
│   │   ├── routes/
│   │   ├── services/
│   │   └── index.ts
│   └── package.json
├── frontend/
│   ├── src/
│   │   ├── components/
│   │   ├── pages/
│   │   └── main.ts
│   └── package.json
└── game-engine/           # Bu proje
    ├── src/
    │   ├── engine/
    │   └── index.ts
    └── package.json
```

## 🔧 Build ve Deploy

### Development
```bash
# Game engine
cd game-engine
npm run dev

# Frontend (başka terminal)
cd frontend
npm run dev

# Backend (başka terminal)
cd backend
npm run dev
```

### Production
```bash
# Game engine'i build et
cd game-engine
npm run build

# Frontend'i build et (game-engine'i kullanarak)
cd frontend
npm run build

# Backend'i build et
cd backend
npm run build
```

## 🚀 Deployment

### Docker ile
```dockerfile
# Dockerfile.game-engine
FROM node:20-alpine
WORKDIR /app
COPY package*.json ./
RUN npm ci --only=production
COPY . .
RUN npm run build
```

### Vercel/Netlify için
Game engine'i statik bir library olarak build edip CDN'e yükleyin:
```bash
npm run build
# dist/ klasörünü CDN'e yükle
```

## 📝 Önemli Notlar

1. **Canvas ID**: Her zaman aynı canvas ID'yi kullanın (`gameCanvas`)
2. **Cleanup**: Component unmount olduğunda `engine.dispose()` çağırın
3. **Performance**: Babylon.js bundle size büyüktür (~2-3MB), code splitting kullanın
4. **TypeScript**: Strict mode aktif, tip güvenliği önemlidir
5. **State Management**: Backend'den gelen state'i doğrudan DOM'a uygulamayın, game loop üzerinden yapın

## 🐛 Sorun Giderme

### Canvas bulunamıyor
```typescript
// Canvas'ın DOM'a mount olduğundan emin olun
useEffect(() => {
  // Canvas DOM'da hazır olduktan sonra engine'i başlat
}, []);
```

### WebGL hatası
```typescript
// WebGL desteğini kontrol edin
const canvas = document.getElementById('gameCanvas') as HTMLCanvasElement;
const gl = canvas.getContext('webgl2') || canvas.getContext('webgl');
if (!gl) {
  console.error('WebGL desteklenmiyor');
}
```

### Bundle size sorunu
```typescript
// Babylon.js'i lazy load edin
const { GameEngine } = await import('@ft-transcendence/game-engine');
```
