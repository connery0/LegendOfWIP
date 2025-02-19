#pragma once
#include <string>

class Texture
{
public:
	explicit Texture( const std::string& imagePath );
	explicit Texture( const std::string& text, TTF_Font *pFont, const Color4f& textColor );
	explicit Texture( const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor );
	Texture( const Texture& other ) = delete;
	Texture& operator=( const Texture& other ) = delete;
	~Texture();

	//void Draw( const Point2f& destBottomLeft = {}, const Rectf& srcRect = {} ) const;
	void Draw(const Point2f & dstBottomLeft, const Rectf & srcRect, const Color4f & overlayColor = Color4f(1, 1, 1, 1)) const;
	void Draw( const Rectf& destRect, const Rectf& srcRect = {}, const Color4f & overlayColor = Color4f(1, 1, 1, 1)) const;

	float GetWidth() const;
	float GetHeight() const;
	bool IsCreationOk( ) const;

private:
	//DATA MEMBERS
	GLuint m_Id{};
	float m_Width{ 10.0f };
	float m_Height{ 10.0f };
	bool m_CreationOk{};

	// FUNCTIONS
	void CreateFromImage( const std::string& path );
	void CreateFromString( const std::string& text, TTF_Font *pFont, const Color4f & textColor );
	void CreateFromString( const std::string& text, const std::string& fontPath, int ptSize, const Color4f& textColor );
	void CreateFromSurface( SDL_Surface *pSurface );
	void DrawFilledRect( const Point2f& dstBottomLeft ) const;
};


