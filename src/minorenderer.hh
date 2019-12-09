#ifndef __MINORENDERER_HH
#define __MINORENDERER_HH

#include "mino.hh"
#include "minotexturestore.hh"
#include "renderable.hh"

class MinoRenderer : public Renderable {
  public:
    MinoRenderer(int referenceX, int referenceY, int width, const Mino& mino,
                 const MinoTextureStore& minoTextureStore)
        : referenceX{referenceX}, referenceY{referenceY}, width{width},
          mino{mino}, minoTextureStore{minoTextureStore} {}
    virtual ~MinoRenderer() {}

    virtual void render(const Renderer& renderer);

  private:
    int referenceX;
    int referenceY;
    int width;
    Mino mino;
    MinoTextureStore minoTextureStore;
};

#endif
