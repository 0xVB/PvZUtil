#include <string>
#include <list>

namespace Sexy
{
#include "Geometry/Geometry.hpp"
#pragma region Enums
    enum Justification
    {
        LeftAlignment = -1,
        CenterAlignment = 0,
        RightAlignment = 1
    };
#pragma endregion
#pragma region PopStructs
	struct PopString
	{
		int Padding;
		std::string String;

		PopString(std::string);
		PopString(const char*);
	};
	template <typename T>
	struct PopList
	{
		int Padding;
		std::list<T> List;

		PopList();
		PopList(std::list<T>);
	};
#pragma endregion

#pragma region Forward Definitions
#pragma region Simple Structs
	struct Color;
    struct TriVertex;
#pragma endregion
	class Image;
	class Graphics;
	class Font;
	class Edge;
	struct GraphicsState;
#pragma endregion

#pragma region Simple Structs
	// Contains colors defined by their RGBA values. (0-255).
	struct Color
	{
		int R;
		int G;
		int B;
		int A;

		Color(int = 0, int = 0, int = 0, int = 255);
		Color(const char* HexCode);

        operator int();
        operator std::string();
	};
    struct TriVertex
    {
        float X;
        float Y;
        float U;
        float V;
        unsigned int Color;
    };
#pragma endregion

#pragma region Definitions
	class GraphicsState
	{
    public:
		Image* DestImage;
		FVec2 Translation;
		FVec2 Scale;
		FVec2 ScaleOrigin;
		IRect ClipRect;
		Color CurrColor;
		Font* CurrFont;
		int DrawMode;
		bool ColorizeImages;
		bool FastStretch;
		bool WriteColoredString;
		bool LinearBlend;
		bool Is3D;
	};
	class Graphics : public GraphicsState
	{
    public:
		Edge* PFActiveEdgeList;
		int PFNumActiveEdges;
		int PFNumVertices;
		std::list<Sexy::GraphicsState> StateStack;

		virtual __thiscall ~Graphics() = 0;

        __thiscall Graphics(const Graphics& G);
        __thiscall Graphics(Image* DestImage);
        
        void __stdcall PushState();
        void __thiscall PopState();
        Graphics* __stdcall Create();

        // Drawing Functions
        void __thiscall ClearClipRect();
        void __thiscall Translate(int X, int Y);

        void __thiscall FillRect(int X, int Y, int W, int H);
        void __thiscall FillRect(const IRect&);

        void __thiscall DrawRect(int X, int Y, int W, int H);
        void __thiscall DrawRect(const IRect&);

        void __stdcall DrawLine(int StartX, int StartY, int EndX, int EndY);

        void __thiscall DrawImage(Image*, int X, int Y);
        void __thiscall DrawImage(Image*, int X, int Y, int W, int H);
        void __thiscall DrawImage(Image*, const IRect& Dest);
        void __thiscall DrawImage(Image*, const IRect& Source, int X, int Y, bool Mirror = false);
        void __thiscall DrawImage(Image*, const IRect& Source, const IRect& Dest, bool Mirror = false);
        void __thiscall DrawImageCell(Image*, int X, int Y, int Cell);
        void __thiscall DrawImageCell(Image*, int X, int Y, int Row, int Col);
        void __thiscall DrawTexturedTriangles(Image* Texture, const TriVertex[][3], int TriangleCount);
    
        void __thiscall DrawString(const PopString& Text, int X, int Y);
        // Returns the X Offset of the string.
        int __thiscall WriteString(const PopString& Text, int X, int Y, int Width, Justification, bool DoDraw = true, int Offset = 0, int Length = -1, int OldColor = 0);
        // Returns the height of the text.
        int __thiscall WriteWordWrapped(const IRect&, const PopString& Text, int LineSpacing = -1, Justification = RightAlignment);
        // Returns the height of the text.
        int __thiscall DrawStringWordWrapped(const PopString& Text, int X, int Y);
        int __thiscall GetWordWrappedHeight(const PopString& Text, int Width, int LineSpacing);
    };

#pragma endregion
}