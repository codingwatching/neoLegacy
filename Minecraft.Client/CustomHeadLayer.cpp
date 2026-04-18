#include "stdafx.h"
#include "CustomHeadLayer.h"
#include "ModelPart.h"
#include "SkullTileRenderer.h"
#include "TileRenderer.h"
#include "../Minecraft.World/ItemInstance.h"
#include "../Minecraft.World/Item.h"
#include "../Minecraft.World/Tile.h"
#include "../Minecraft.World/LivingEntity.h"

CustomHeadLayer::CustomHeadLayer(ModelPart* headPart)
    : headPart(headPart)
{
}

int CustomHeadLayer::colorsOnDamage()
{
    return 1;
}

void CustomHeadLayer::render(shared_ptr<LivingEntity> mob,
                              float wp, float ws, float bob,
                              float headRot, float headRotX,
                              float scale, bool useCompiled)
{
    ItemInstanceArray slots = mob->getEquipmentSlots();
    if (slots.length < 5) return;
    shared_ptr<ItemInstance> helmet = slots[4];
    if (!helmet) return;
    Item* item = helmet->getItem();
    if (!item) return;

    bool hasHatLayer = false;
    if (mob->instanceof(eTYPE_PLAYER)) {
        _SkinAdjustments adj;
        mob->getSkinAdjustments(&adj);
        hasHatLayer = (adj.data[0] & 0x100) != 0;
    }

    glPushMatrix();
    headPart->translateTo(0.0625f);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    int itemId = item->id;

  if (itemId == Tile::skull_Id) {
    if (!SkullTileRenderer::instance) { glPopMatrix(); return; }
    glScalef(1.1875f, -1.1875f, -1.1875f);
    glTranslatef(-0.5f, 0.0f, -0.5f);
    int skullType = helmet->getAuxValue() & 0xF;
    wstring extra = helmet->hasTag() ? helmet->getTag()->getString(L"SkullOwner") : L"";
    SkullTileRenderer::instance->renderSkull(0.0f, 0.0f, 0.0f, -1, 180.0f, skullType, extra);
    }  else if (itemId < 0x100) {
    glTranslatef(0.0f, -0.25f, 0.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glScalef(0.625f, 0.625f, 0.625f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    if (itemId > 0 && itemId < Tile::TILE_NUM_COUNT && Tile::tiles[itemId]) {
        TileRenderer tr;
        tr.renderTile(Tile::tiles[itemId], helmet->getAuxValue(), 1.0f, 1.0f, useCompiled);
    }
}

    glPopMatrix();
}