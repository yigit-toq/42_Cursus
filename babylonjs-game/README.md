# ft_transcendence - Game Engine

3D Pong oyunu için Babylon.js tabanlı modüler oyun motoru.

## 🎯 Proje Yapısı

```
babylonjs-game/
├── src/
│   ├── engine/           # Motor bileşenleri
│   │   ├── core/         # GameEngine, GameLoop
│   │   ├── ecs/          # Entity Component System (gelecek)
│   │   ├── input/        # Input yönetimi (gelecek)
│   │   ├── physics/      # Fizik wrapper'ları (gelecek)
│   │   └── render/       # SceneManager, render sistemi
│   ├── game/             # Oyun-spesifik kod (Pong)
│   ├── ui/               # UI bileşenleri
│   ├── types/            # TypeScript tip tanımları
│   ├── index.ts          # Public API export
│   └── dev.ts            # Development entry point
├── docs/                 # Dokümantasyon (gelecek)
├── tests/                # Test dosyaları (gelecek)
└── public/               # Statik asset'ler
```

## 🚀 Kurulum

```bash
npm install
```

## 💻 Geliştirme

Development server'ı başlat (Vite):

```bash
npm run dev
```

Tarayıcıda http://localhost:3000 açılacak.

## 🏗️ Build

Production build oluştur:

```bash
npm run build
```

Build çıktısı `dist/` klasöründe olacak.

## 📦 Entegrasyon

Bu motor, frontend projenize module olarak entegre edilebilir:

```typescript
import { GameEngine, SceneManager } from '@ft-transcendence/game-engine';

// Motor'u başlat
const engine = new GameEngine({
  canvasId: 'gameCanvas',
  antialias: true,
});

// Sahne yöneticisi oluştur
const sceneManager = new SceneManager(engine);
sceneManager.setupDefaultCamera();
sceneManager.setupDefaultLighting();

// Sahneyi ayarla ve başlat
engine.setScene(sceneManager.getScene());
engine.start();
```

## 🛠️ Tech Stack

- **TypeScript** 5.6+ (Strict mode)
- **Babylon.js** 7.31+ (3D rendering)
- **Vite** 5.4+ (Build tool)
- **ES Modules** (Modern module system)

## 📋 Issue'lar ve Roadmap

GitHub Issues'da tanımlanmış modüler geliştirme planı:

- ✅ #1: Core Engine Architecture & Folder Structure
- ⏳ #2: Deterministic Fixed-Timestep Game Loop
- ⏳ #3: Lightweight ECS Framework
- ⏳ #4: Input Manager System
- ⏳ #5: Physics Integration & Utilities
- ⏳ #6: Scene Manager & Camera Setup
- ⏳ #7: PongGame Core State & Rules

## 🎮 Özellikler

### Mevcut
- ✅ Modüler motor yapısı
- ✅ Babylon.js entegrasyonu
- ✅ TypeScript strict mode
- ✅ Vite development server
- ✅ Scene yönetimi
- ✅ Kamera ve ışık sistemi

### Gelecek
- ⏳ Fixed timestep game loop
- ⏳ ECS (Entity Component System)
- ⏳ Input manager
- ⏳ Physics integration (Havok)
- ⏳ Pong oyunu implementasyonu
- ⏳ Multiplayer desteği
- ⏳ UI sistemi

## 📝 Notlar

- Motor, backend'den **bağımsız** çalışacak şekilde tasarlandı
- Kolay entegrasyon için module olarak export ediliyor
- Game loop ve state yönetimi **deterministic** olacak
- WebSocket üzerinden multiplayer senkronizasyonu desteklenecek

## 📄 Lisans

MIT
