SceneView，GameView，AssetsView继承自AView

View本身的渲染是imgui，AView::_Draw_Impl
View中Actor的渲染是AView::_Render_Impl

思路是添加2D Sprite的Actor，基类Node
然后添加UI下的Button，继承自Control
仿照godot的设计

第一步先写场景下的Sprite

一个Sprite类(texture, mesh, uv, triangle, position, rotation, scale)，包含SpriteRenderer(sprite, materialname)和MaterialRenderer(material)

创建ButtonComponent，添加到Sprite上，支持按钮点击(Unity的Button可以添加到Sprite上，但是没有TargetGraphic)


第二步，开发Canvas，支持传统UI，Button，Text，Input，RichText等

一般游戏引擎的Sprite都是场景下的，Button等才是UI下