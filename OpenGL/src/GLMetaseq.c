/*
	2014/11/5 �ｿｽZ�ｿｽL�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽe�ｿｽB�ｿｽﾎ搾ｿｽ�ｿｽﾅ（Visual Studio 2013�ｿｽﾎ会ｿｽ�ｿｽj
*/
#define __GLMETASEQ_C__
#include "GLMetaseq.h"

/*

GLMetaseq
The MIT License
Copyright (c) 2009 Sunao Hashimoto and Keisuke Konishi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.


GLMetaseq
MIT�ｿｽ�ｿｽ�ｿｽC�ｿｽZ�ｿｽ�ｿｽ�ｿｽX
Copyright (c) 2009 Sunao Hashimoto and Keisuke Konishi

�ｿｽﾈ会ｿｽ�ｿｽﾉ抵ｿｽﾟゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾉ従�ｿｽ�ｿｽ�ｿｽA�ｿｽ{�ｿｽ\�ｿｽt�ｿｽg�ｿｽE�ｿｽF�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽﾑ関連�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌフ�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽi�ｿｽﾈ会ｿｽ�ｿｽu�ｿｽ\�ｿｽt�ｿｽg
�ｿｽE�ｿｽF�ｿｽA�ｿｽv�ｿｽj�ｿｽﾌ包ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ謫ｾ�ｿｽ�ｿｽ�ｿｽ驍ｷ�ｿｽﾗての人�ｿｽﾉ対ゑｿｽ�ｿｽA�ｿｽ\�ｿｽt�ｿｽg�ｿｽE�ｿｽF�ｿｽA�ｿｽｳ撰ｿｽ�ｿｽ�ｿｽ�ｿｽﾉ茨ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾆゑｿｽ
�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾅ具ｿｽ�ｿｽﾂゑｿｽ�ｿｽﾜゑｿｽ�ｿｽB�ｿｽ�ｿｽ�ｿｽ�ｿｽﾉは、�ｿｽ\�ｿｽt�ｿｽg�ｿｽE�ｿｽF�ｿｽA�ｿｽﾌ包ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽg�ｿｽp�ｿｽA�ｿｽ�ｿｽ�ｿｽﾊ、�ｿｽﾏ更�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽA�ｿｽf�ｿｽﾚ、
�ｿｽﾐ布�ｿｽA�ｿｽT�ｿｽu�ｿｽ�ｿｽ�ｿｽC�ｿｽZ�ｿｽ�ｿｽ�ｿｽX�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ/�ｿｽﾜゑｿｽ�ｿｽﾍ販費ｿｽ�ｿｽ�ｿｽ�ｿｽ骭��ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽﾑソ�ｿｽt�ｿｽg�ｿｽE�ｿｽF�ｿｽA�ｿｽ�ｿｽ氓�ｿｽ�ｿｽ�ｿｽ
�ｿｽ�ｿｽ�ｿｽ�ｿｽﾉ難ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾆゑｿｽ�ｿｽ�ｿｽ�ｿｽﾂゑｿｽ�ｿｽ骭��ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾉ含まゑｿｽﾜゑｿｽ�ｿｽB

�ｿｽ�ｿｽL�ｿｽﾌ抵ｿｽ�ｿｽ�権�ｿｽ\�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾑ本�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ\�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽA�ｿｽ\�ｿｽt�ｿｽg�ｿｽE�ｿｽF�ｿｽA�ｿｽﾌゑｿｽ�ｿｽﾗての包ｿｽ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ�ｿｽﾍ重�ｿｽv�ｿｽﾈ包ｿｽ�ｿｽ�ｿｽ
�ｿｽﾉ記�ｿｽﾚゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌとゑｿｽ�ｿｽﾜゑｿｽ�ｿｽB

�ｿｽ\�ｿｽt�ｿｽg�ｿｽE�ｿｽF�ｿｽA�ｿｽﾍ「�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌまま」�ｿｽﾅ、�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾅゑｿｽ�ｿｽ驍ｩ�ｿｽﾃ黙でゑｿｽ�ｿｽ驍ｩ�ｿｽ�ｿｽ�ｿｽ墲ｸ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌ保擾ｿｽ
�ｿｽ�ｿｽ�ｿｽﾈゑｿｽ�ｿｽ氓�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ�ｿｽB�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾅゑｿｽ�ｿｽ�ｿｽ�ｿｽﾛ証とは、�ｿｽ�ｿｽ�ｿｽi�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌ目的�ｿｽﾖの適�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽN�ｿｽQ�ｿｽﾉつゑｿｽ�ｿｽﾄの保証ゑｿｽ�ｿｽﾜみまゑｿｽ�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽﾉ鯉ｿｽ�ｿｽ閧ｳ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌではゑｿｽ�ｿｽ�ｿｽﾜゑｿｽ�ｿｽ�ｿｽB
�ｿｽ�ｿｽﾒまゑｿｽ�ｿｽﾍ抵ｿｽ�ｿｽ�権�ｿｽﾒは、�ｿｽ_�ｿｽ�ｿｽs�ｿｽﾗ、�ｿｽs�ｿｽ@�ｿｽs�ｿｽﾗ、�ｿｽﾜゑｿｽ�ｿｽﾍゑｿｽ�ｿｽ�ｿｽﾈ外�ｿｽﾅゑｿｽ�ｿｽ�う�ｿｽﾆ、�ｿｽ\�ｿｽt�ｿｽg
�ｿｽE�ｿｽF�ｿｽA�ｿｽﾉ起�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ�ｿｽﾍ関連�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ驍｢�ｿｽﾍソ�ｿｽt�ｿｽg�ｿｽE�ｿｽF�ｿｽA�ｿｽﾌ使�ｿｽp�ｿｽﾜゑｿｽ�ｿｽﾍゑｿｽ�ｿｽﾌ托ｿｽ�ｿｽﾌ茨ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄ撰ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾘの撰ｿｽ�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽQ�ｿｽA�ｿｽ�ｿｽ�ｿｽﾌ托ｿｽ�ｿｽﾌ義�ｿｽ�ｿｽ�ｿｽﾉつゑｿｽ�ｿｽﾄ会ｿｽ�ｿｽ�ｿｽﾌ責任�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾈゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽﾆゑｿｽ�ｿｽﾜゑｿｽ�ｿｽB

*/

/*=========================================================================
�ｿｽy�ｿｽ�ｿｽ�ｿｽﾌソ�ｿｽ[�ｿｽX�ｿｽ�ｿｽ�ｿｽﾅのみ有�ｿｽ�ｿｽ�ｿｽﾈグ�ｿｽ�ｿｽ�ｿｽ[�ｿｽo�ｿｽ�ｿｽ�ｿｽﾏ撰ｿｽ�ｿｽz
=========================================================================*/

static TEXTURE_POOL l_texPool[MAX_TEXTURE];		// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽv�ｿｽ[�ｿｽ�ｿｽ
static int			l_texPoolnum;				// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾌ撰ｿｽ
static int			l_GLMetaseqInitialized = 0;	// �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽt�ｿｽ�ｿｽ�ｿｽO


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽ骭ｾ�ｿｽz
=========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

	void	endianConverter(void *addr, unsigned int size);
	void	TGAHeaderEndianConverter(STR_TGA_HEAD *tgah);
	int		IsExtensionSupported(char* szTargetExtension);

	GLuint		mqoSetTexturePool(char *texfile, char *alpfile, unsigned char alpha);
	void		mqoClearTexturePool();
	GLubyte*	mqoLoadTextureEx(char *texfile, char *alpfile, int *tex_size, unsigned char alpha);
	int			mqoLoadFile(MQO_OBJECT *mqoobj, char *filename, double scale, unsigned char alpha);
	MQO_OBJECT*	mqoCreateList(int num);
	int			mqoCreateListObject(MQO_OBJECT *obj, int id, char *filename, double scale, unsigned char alpha);

	void mqoCallListObject(MQO_OBJECT object[], int num);
	void mqoClearObject(MQO_OBJECT object[], int from, int num);
	void mqoDeleteObject(MQO_OBJECT * object, int num);
	void mqoGetDirectory(const char *path_file, char *path_dir);
	void mqoSnormal(glPOINT3f A, glPOINT3f B, glPOINT3f C, glPOINT3f *normal);
	void mqoReadMaterial(FILE *fp, MQO_MATDATA M[]);
	void mqoReadVertex(FILE *fp, glPOINT3f V[]);
	int	 mqoReadBVertex(FILE *fp, glPOINT3f V[]);
	void mqoReadFace(FILE *fp, MQO_FACE F[]);
	void mqoReadObject(FILE *fp, MQO_OBJDATA *obj);

	void mqoMakeArray(MQO_MATERIAL *mat, int matpos, MQO_FACE F[], int fnum, glPOINT3f V[],
		glPOINT3f N[], double facet, glCOLOR4f *mcol, double scale, unsigned char alpha);

	glPOINT3f *mqoVertexNormal(MQO_OBJDATA *obj);

	void mqoMakePolygon(MQO_OBJDATA *readObj, MQO_OBJECT *mqoobj,
		glPOINT3f N[], MQO_MATDATA M[], int n_mat, double scale, unsigned char alpha);

	void mqoMakeObjectsEx(MQO_OBJECT *mqoobj, MQO_OBJDATA obj[], int n_obj, MQO_MATDATA M[], int n_mat,
		double scale, unsigned char alpha);

#ifdef __cplusplus
}
#endif

/*=========================================================================
�ｿｽy�ｿｽZ�ｿｽL�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽe�ｿｽB�ｿｽﾎ搾ｿｽ�ｿｽp�ｿｽ}�ｿｽN�ｿｽ�ｿｽ�ｿｽz Visual C++ 2005�ｿｽﾈ降
=========================================================================*/
#if _MSC_VER >=1400
#define strcpy(dst, src) strncpy_s(dst, SIZE_STR, src, SIZE_STR)
#define strncpy(dst, src, len) strncpy_s(dst, SIZE_STR, src, len)
#define sscanf(src, ...) sscanf_s(src, __VA_ARGS__, SIZE_STR)
#define sprintf(buf, ...) sprintf_s(buf, SIZE_STR, __VA_ARGS__)
#endif

/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzendianConverter
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽG�ｿｽ�ｿｽ�ｿｽf�ｿｽB�ｿｽA�ｿｽ�ｿｽ�ｿｽﾏ奇ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
addr	�ｿｽA�ｿｽh�ｿｽ�ｿｽ�ｿｽX
size	�ｿｽT�ｿｽC�ｿｽY

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void endianConverter(void *addr, unsigned int size)
{
	unsigned int pos;
	char c;
	if (size <= 1) return;
	for (pos = 0; pos < size / 2; pos++) {
		c = *(((char *)addr) + pos);
		*(((char *)addr) + pos) = *(((char *)addr) + (size - 1 - pos));
		*(((char *)addr) + (size - 1 - pos)) = c;
	}
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzTGAHeaderEndianConverter
�ｿｽy�ｿｽp�ｿｽr�ｿｽzTGA�ｿｽﾌヘ�ｿｽb�ｿｽ_�ｿｽﾌエ�ｿｽ�ｿｽ�ｿｽf�ｿｽB�ｿｽA�ｿｽ�ｿｽ�ｿｽﾏ奇ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
tgah	TGA�ｿｽﾌヘ�ｿｽb�ｿｽ_

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void TGAHeaderEndianConverter(STR_TGA_HEAD *tgah)
{
	endianConverter(&tgah->color_map_entry, sizeof(tgah->color_map_entry));
	endianConverter(&tgah->x, sizeof(tgah->x));
	endianConverter(&tgah->y, sizeof(tgah->y));
	endianConverter(&tgah->width, sizeof(tgah->width));
	endianConverter(&tgah->height, sizeof(tgah->height));
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzIsExtensionSupported
�ｿｽy�ｿｽp�ｿｽr�ｿｽzOpenGL�ｿｽﾌ拡�ｿｽ�ｿｽ�ｿｽ@�ｿｽ\�ｿｽ�ｿｽ�ｿｽT�ｿｽ|�ｿｽ[�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ驍ｩ�ｿｽﾇゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾗゑｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
szTargetExtension	�ｿｽg�ｿｽ�ｿｽ�ｿｽ@�ｿｽ\�ｿｽﾌ厄ｿｽ�ｿｽO

�ｿｽy�ｿｽﾟ値�ｿｽz1�ｿｽF�ｿｽT�ｿｽ|�ｿｽ[�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ�ｿｽC0�ｿｽF�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽﾈゑｿｽ
=========================================================================*/

int IsExtensionSupported(char* szTargetExtension)
{
	const unsigned char *pszExtensions = NULL;
	const unsigned char *pszStart;
	unsigned char *pszWhere, *pszTerminator;

	// Extension �ｿｽﾌ厄ｿｽ�ｿｽO�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾗゑｿｽ(NULL�ｿｽ�ｿｽ窒�ｿｽNG�ｿｽj
	pszWhere = (unsigned char *)strchr(szTargetExtension, ' ');
	if (pszWhere || *szTargetExtension == (char)NULL)
		return 0;

	// Extension �ｿｽﾌ包ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
	pszExtensions = glGetString(GL_EXTENSIONS);

	// �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌ抵ｿｽ�ｿｽﾉ必�ｿｽv�ｿｽ�ｿｽ extension �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ驍ｩ�ｿｽ�ｿｽ�ｿｽﾗゑｿｽ
	pszStart = pszExtensions;
	for (;;)
	{
		pszWhere = (unsigned char *)strstr((const char *)pszStart, szTargetExtension);
		if (!pszWhere)
			break;
		pszTerminator = pszWhere + strlen(szTargetExtension);
		if (pszWhere == pszStart || *(pszWhere - 1) == ' ')
			if (*pszTerminator == ' ' || *pszTerminator == (char)NULL)
				return 1;
		pszStart = pszTerminator;
	}
	return 0;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoInit
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ�ｿｽ�ｿｽ^�ｿｽZ�ｿｽR�ｿｽC�ｿｽA�ｿｽ�ｿｽ�ｿｽ[�ｿｽ_�ｿｽﾌ擾ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void mqoInit(void)
{
	// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽv�ｿｽ[�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
	memset(l_texPool, 0, sizeof(l_texPool));
	l_texPoolnum = 0;

	// �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽﾌサ�ｿｽ|�ｿｽ[�ｿｽg�ｿｽﾌチ�ｿｽF�ｿｽb�ｿｽN
	g_isVBOSupported = IsExtensionSupported("GL_ARB_vertex_buffer_object");
	//	g_isVBOSupported = 0;

#ifdef WIN32
	glGenBuffersARB = NULL;
	glBindBufferARB = NULL;
	glBufferDataARB = NULL;
	glDeleteBuffersARB = NULL;

	if (g_isVBOSupported) {
		// printf("OpenGL : �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽ�ｿｽ�ｿｽT�ｿｽ|�ｿｽ[�ｿｽg�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ�ｿｽﾌで使�ｿｽp�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ\n");
		// GL �ｿｽﾖ撰ｿｽ�ｿｽﾌポ�ｿｽC�ｿｽ�ｿｽ�ｿｽ^�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
	}
#endif

	// �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽt�ｿｽ�ｿｽ�ｿｽO
	l_GLMetaseqInitialized = 1;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoCleanup
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ�ｿｽ�ｿｽ^�ｿｽZ�ｿｽR�ｿｽC�ｿｽA�ｿｽ�ｿｽ�ｿｽ[�ｿｽ_�ｿｽﾌ終�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void mqoCleanup(void)
{
	mqoClearTexturePool();	// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽv�ｿｽ[�ｿｽ�ｿｽ�ｿｽﾌク�ｿｽ�ｿｽ�ｿｽA
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoSetTexturePool
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽv�ｿｽ[�ｿｽ�ｿｽ�ｿｽﾉテ�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
texfile		�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ
alpfile		�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ
alpha		�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽID
�ｿｽy�ｿｽd�ｿｽl�ｿｽz�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽﾜゑｿｽﾄゑｿｽ�ｿｽﾈゑｿｽ�ｿｽ�ｿｽﾎ読み搾ｿｽ�ｿｽﾝ，�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽo�ｿｽ^
�ｿｽ�ｿｽ�ｿｽﾅに読み搾ｿｽ�ｿｽﾜゑｿｽﾄゑｿｽ�ｿｽ�ｿｽﾎ登�ｿｽ^�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌゑｿｽﾔゑｿｽ.
=========================================================================*/

GLuint mqoSetTexturePool(char *texfile, char *alpfile, unsigned char alpha)
{
	int pos;
	GLubyte *image;

	for (pos = 0; pos < l_texPoolnum; pos++) {
		if (alpha != l_texPool[pos].alpha) {
			continue;
		}
		if (texfile != NULL) {
			if (strcmp(texfile, l_texPool[pos].texfile) != 0) {
				continue;
			}
		}
		if (alpfile != NULL) {
			if (strcmp(alpfile, l_texPool[pos].alpfile) != 0) {
				continue;
			}
		}
		break;
	}
	if (pos < l_texPoolnum) { //�ｿｽ�ｿｽ�ｿｽﾅに読み搾ｿｽ�ｿｽﾝ済ゑｿｽ
		return  l_texPool[pos].texture_id;
	}
	if (MAX_TEXTURE <= pos) {
		printf("%s:mqoSetTexturePool �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽﾝ領茨ｿｽs�ｿｽ�ｿｽ\n", __FILE__);
		return -1;
	}
	image = mqoLoadTextureEx(texfile, alpfile, &l_texPool[pos].texsize, alpha);
	if (image == NULL) {
		return -1;
	}

	if (texfile != NULL) strncpy(l_texPool[pos].texfile, texfile, MAX_PATH);
	if (alpfile != NULL) strncpy(l_texPool[pos].alpfile, alpfile, MAX_PATH);
	l_texPool[pos].alpha = alpha;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glPixelStorei(GL_PACK_ALIGNMENT, 4);
	glGenTextures(1, &l_texPool[pos].texture_id);			// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽｶ撰ｿｽ
	glBindTexture(GL_TEXTURE_2D, l_texPool[pos].texture_id);	// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾌ奇ｿｽ�ｿｽ闢厄ｿｽ�ｿｽ

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, l_texPool[pos].texsize, l_texPool[pos].texsize,
		0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	l_texPoolnum = pos + 1;

	//�ｿｽo�ｿｽ^�ｿｽ�ｿｽ�ｿｽ�ｿｽﾎ、�ｿｽﾇみ搾ｿｽ�ｿｽｾバ�ｿｽb�ｿｽt�ｿｽ@�ｿｽﾍ不�ｿｽv
	free(image);
	glBindTexture(GL_TEXTURE_2D, 0);	// �ｿｽf�ｿｽt�ｿｽH�ｿｽ�ｿｽ�ｿｽg�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾌ奇ｿｽ�ｿｽ闢厄ｿｽ�ｿｽ

	return l_texPool[pos].texture_id;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoClearTexturePool()
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽv�ｿｽ[�ｿｽ�ｿｽ�ｿｽﾌ開�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void mqoClearTexturePool()
{
	int pos;
	for (pos = 0; pos < l_texPoolnum; pos++) {
		glDeleteTextures(1, &l_texPool[pos].texture_id);	// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ尞�
	}

	memset(l_texPool, 0, sizeof(l_texPool));
	l_texPoolnum = 0;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoLoadTextureEx
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽ鞫懶ｿｽ�ｿｽ�ｿｽ�成�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
texfile		�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ
alpfile		�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ
tex_size	�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾌサ�ｿｽC�ｿｽY�ｿｽi�ｿｽ�ｿｽﾓの抵ｿｽ�ｿｽ�ｿｽ�ｿｽj�ｿｽ�ｿｽﾔゑｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽ鞫懶ｿｽﾖのポ�ｿｽC�ｿｽ�ｿｽ�ｿｽ^�ｿｽi�ｿｽ�ｿｽ�ｿｽs�ｿｽ�ｿｽ�ｿｽ�ｿｽNULL�ｿｽj
�ｿｽy�ｿｽd�ｿｽl�ｿｽz24bit�ｿｽr�ｿｽb�ｿｽg�ｿｽ}�ｿｽb�ｿｽv�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ8,24,32bit�ｿｽs�ｿｽf�ｿｽ`
�ｿｽT�ｿｽC�ｿｽY�ｿｽﾍ「�ｿｽ�ｿｽﾓゑｿｽ2�ｿｽ�ｿｽn�ｿｽ�ｿｽﾌ撰ｿｽ�ｿｽ�ｿｽ�ｿｽ`�ｿｽv�ｿｽﾉ鯉ｿｽ�ｿｽ�ｿｽ
libjpeg,libpng�ｿｽi�ｿｽO�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽC�ｿｽu�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽj�ｿｽ�ｿｽ�ｿｽL�ｿｽ�ｿｽ�ｿｽJPEG,PNG�ｿｽﾌ読み搾ｿｽ�ｿｽﾝ可能
=========================================================================*/

GLubyte* mqoLoadTextureEx(char *texfile, char *alpfile, int *tex_size, unsigned char alpha)
{
	FILE *fp;
	size_t namelen;
	char ext[4];
	char wbuf[3];
	int isTGA;
	int isPNG;
	int isJPEG;
	int other;
	int	y, x, size;
	int fl;
	char *filename[2];
	int width[2];
	int sts;
	STR_TGA_HEAD tgah;
	GLubyte	*pImage, *pRead;
	errno_t err;

#if DEF_USE_LIBJPEG
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	JSAMPARRAY jpegimage;
#endif
#if DEF_USE_LIBPNG
	unsigned char **pngimage;
	unsigned long   pngwidth, pngheight;
	int				pngdepth;
	int             color_type;
#endif

	filename[0] = texfile;
	filename[1] = alpfile;
	width[0] = -1;
	width[1] = -1;
	pImage = NULL;
	fp = NULL;
	sts = 0;
#if DEF_USE_LIBJPEG
	jpegimage = NULL;
#endif
#if DEF_USE_LIBPNG
	pngimage = NULL;
#endif
	size = -1;
	for (fl = 0; fl < 2; fl++) {//�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽfl=0    �ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽ�ｿｽfl=1
		if (filename[fl] == NULL) continue;
		namelen = strlen(filename[fl]);
		ext[0] = tolower(filename[fl][namelen - 3]);
		ext[1] = tolower(filename[fl][namelen - 2]);
		ext[2] = tolower(filename[fl][namelen - 1]);
		ext[3] = 0x00;
		isTGA = (strcmp(ext, "tga") == 0) ? 1 : 0;
		isPNG = (strcmp(ext, "png") == 0) ? 1 : 0;
		isJPEG = (strcmp(ext, "jpg") == 0) ? 1 : 0;
		/* */
		if ((!isTGA) && (!isPNG) && (!isJPEG)) {
			filename[fl][namelen - 3] = 'b';
			filename[fl][namelen - 2] = 'm';
			filename[fl][namelen - 1] = 'p';
		}
		/* */
		if (fl == 1) { //�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽﾌ読み搾ｿｽ�ｿｽﾝはＴ�ｿｽf�ｿｽ`or�ｿｽo�ｿｽm�ｿｽf
			if (!(isTGA || isPNG)) {
				printf("�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽﾌフ�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾉ対会ｿｽ�ｿｽﾅゑｿｽ�ｿｽﾈゑｿｽ�ｿｽ�ｿｽ%s\n", filename[fl]);
				break;
			}
		}
		if (fp != NULL) fclose(fp);
#if _MSC_VER >=1400
		err = fopen_s(&fp, filename[fl], "rb");
		if (err != 0) {
#else
		if ((fp = fopen(filename[fl], "rb")) == NULL) {
#endif
			printf("%s:�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽﾝエ�ｿｽ�ｿｽ�ｿｽ[[%s]\n", __FILE__, filename[fl]);
			continue;
		}
		// �ｿｽw�ｿｽb�ｿｽ_�ｿｽﾌ��ｿｽ�ｿｽ[�ｿｽh
		if (isTGA) {
			fread(&tgah, sizeof(STR_TGA_HEAD), 1, fp);
#if DEF_IS_LITTLE_ENDIAN
#else
			TGAHeaderEndianConverter(&tgah);
#endif
			size = width[fl] = tgah.width;
		}
		if (isJPEG) {
#if DEF_USE_LIBJPEG
			unsigned int i;
			cinfo.err = jpeg_std_error(&jerr);
			jpeg_create_decompress(&cinfo);	//�ｿｽ用�ｿｽ�ｿｽ�ｿｽ�成
			jpeg_stdio_src(&cinfo, fp);		//�ｿｽﾇみ搾ｿｽ�ｿｽﾝフ�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽw�ｿｽ�ｿｽ
			jpeg_read_header(&cinfo, TRUE);	//jpeg�ｿｽw�ｿｽb�ｿｽ_�ｿｽﾇみ搾ｿｽ�ｿｽ�ｿｽ
			jpeg_start_decompress(&cinfo);	//�ｿｽ開�ｿｽn

			if (cinfo.out_color_components == 3 && cinfo.out_color_space == JCS_RGB) {
				if (jpegimage != NULL) {
					for (i = 0; i < cinfo.output_height; i++) free(jpegimage[i]);            // �ｿｽﾈ会ｿｽ�ｿｽQ�ｿｽs�ｿｽﾍ２�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ
					free(jpegimage);
				}
				//�ｿｽﾇみ搾ｿｽ�ｿｽﾝデ�ｿｽ[�ｿｽ^�ｿｽz�ｿｽ�ｿｽﾌ作成
				jpegimage = (JSAMPARRAY)malloc(sizeof(JSAMPROW) * cinfo.output_height);
				for (i = 0; i < cinfo.output_height; i++) {
					jpegimage[i] = (JSAMPROW)malloc(sizeof(JSAMPLE) * cinfo.out_color_components * cinfo.output_width);
				}
				//�ｿｽデ�ｿｽ[�ｿｽ^�ｿｽﾇみ搾ｿｽ�ｿｽ�ｿｽ
				while (cinfo.output_scanline < cinfo.output_height) {
					jpeg_read_scanlines(&cinfo,
						jpegimage + cinfo.output_scanline,
						cinfo.output_height - cinfo.output_scanline
						);
				}
				size = width[fl] = cinfo.output_width;
			}

			jpeg_finish_decompress(&cinfo);	//�ｿｽ終�ｿｽ�ｿｽ
			jpeg_destroy_decompress(&cinfo);	//�ｿｽ用�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
			if (!(cinfo.out_color_components == 3 && cinfo.out_color_space == JCS_RGB)) {
				printf("JPEG �ｿｽﾎ会ｿｽ�ｿｽﾅゑｿｽ�ｿｽﾈゑｿｽ�ｿｽt�ｿｽH�ｿｽ[�ｿｽ}�ｿｽb�ｿｽg�ｿｽ�ｿｽ%s\n", filename[fl]);
			}
#else
			printf("�ｿｽ�ｿｽ�ｿｽﾌテ�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾍ対会ｿｽ�ｿｽﾅゑｿｽ�ｿｽﾈゑｿｽ�ｿｽt�ｿｽH�ｿｽ[�ｿｽ}�ｿｽb�ｿｽg�ｿｽ�ｿｽ%s\n", filename[fl]);
			continue;
#endif
		}
		if (isPNG) {
#if DEF_USE_LIBPNG
			png_structp     png_ptr;
			png_infop       info_ptr;
			int             bit_depth, interlace_type;
			unsigned int             i;
			int j, k;
			png_ptr = png_create_read_struct(                       // png_ptr�ｿｽ\�ｿｽ�ｿｽ�ｿｽﾌゑｿｽ�ｿｽm�ｿｽﾛ・�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ
				PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
			info_ptr = png_create_info_struct(png_ptr);             // info_ptr�ｿｽ\�ｿｽ�ｿｽ�ｿｽﾌゑｿｽ�ｿｽm�ｿｽﾛ・�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ
			png_init_io(png_ptr, fp);                               // libpng�ｿｽ�ｿｽfp�ｿｽ�ｿｽm�ｿｽ轤ｹ�ｿｽﾜゑｿｽ
			png_read_info(png_ptr, info_ptr);                       // PNG�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾌヘ�ｿｽb�ｿｽ_�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽﾝまゑｿｽ
			png_get_IHDR(png_ptr, info_ptr, &pngwidth, &pngheight,        // IHDR�ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽN�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ謫ｾ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ
				&bit_depth, &color_type, &interlace_type,
				&j, &k);
			if (pngimage != NULL) {
				for (i = 0; i < pngheight; i++) free(pngimage[i]);            // �ｿｽﾈ会ｿｽ�ｿｽQ�ｿｽs�ｿｽﾍ２�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ
				free(pngimage);
			}
			pngimage = (png_bytepp)malloc(pngheight * sizeof(png_bytep)); // �ｿｽﾈ会ｿｽ�ｿｽR�ｿｽs�ｿｽﾍ２�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ�ｿｽ�ｿｽm�ｿｽﾛゑｿｽ�ｿｽﾜゑｿｽ
			i = png_get_rowbytes(png_ptr, info_ptr);
			pngdepth = i / pngwidth;
			for (i = 0; i < pngheight; i++)
				pngimage[i] = (png_bytep)malloc(png_get_rowbytes(png_ptr, info_ptr));
			png_read_image(png_ptr, pngimage);                         // �ｿｽ鞫懶ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽﾝまゑｿｽ

			png_destroy_read_struct(                                // �ｿｽQ�ｿｽﾂの構�ｿｽ�ｿｽ�ｿｽﾌの��ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ
				&png_ptr, &info_ptr, (png_infopp)NULL);
			size = width[fl] = pngwidth;
#else
			printf("�ｿｽ�ｿｽ�ｿｽﾌテ�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾍ対会ｿｽ�ｿｽﾅゑｿｽ�ｿｽﾈゑｿｽ�ｿｽt�ｿｽH�ｿｽ[�ｿｽ}�ｿｽb�ｿｽg�ｿｽ�ｿｽ%s\n", filename[fl]);
			continue;
#endif
		}
		if (width[fl] == -1) {//�ｿｽR�ｿｽR�ｿｽﾜでゑｿｽ�ｿｽﾄサ�ｿｽC�ｿｽY�ｿｽ�ｿｽ�ｿｽw�ｿｽ閧ｳ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽﾈゑｿｽ�ｿｽ@�ｿｽ�ｿｽ�ｿｽ@�ｿｽr�ｿｽb�ｿｽg�ｿｽ}�ｿｽb�ｿｽv
			fseek(fp, 14 + 4, SEEK_SET);		// �ｿｽ鞫懶ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽi�ｿｽ[�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ�ｿｽﾊ置�ｿｽﾜでシ�ｿｽ[�ｿｽN
			fread(&size, sizeof(int), 1, fp);	// BiWidth�ｿｽﾌ擾ｿｽｾゑｿｽ�ｿｽ謫ｾ
			fseek(fp, 14 + 40, SEEK_SET);		// �ｿｽ�ｿｽf�ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽ�ｿｽi�ｿｽ[�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ�ｿｽﾊ置�ｿｽﾜでシ�ｿｽ[�ｿｽN
#if DEF_IS_LITTLE_ENDIAN
#else
			endianConverter(&size, sizeof(int));
#endif
			width[fl] = size;

		}
		if (width[0] != -1 && width[1] != -1) {
			if (width[0] != width[1]) {
				sts = -1;
				break;
			}
		}
		if (fl == 1 && isTGA) { //�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽﾌ読み搾ｿｽ�ｿｽﾝはＴ�ｿｽf�ｿｽ`�ｿｽﾌ８�ｿｽr�ｿｽb�ｿｽg�ｿｽ�ｿｽ�ｿｽm�ｿｽN�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽR�ｿｽQ�ｿｽr�ｿｽb�ｿｽg�ｿｽt�ｿｽ�ｿｽ
			if (!(
				(tgah.depth == 8 && tgah.type == DEF_TGA_TYPE_MONO) ||
				(tgah.depth == 32 && tgah.type == DEF_TGA_TYPE_FULL)
				)) {
				break;
			}
		}
		if (fl == 1 && isPNG) { //�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽﾌ読み搾ｿｽ�ｿｽﾝはＰ�ｿｽm�ｿｽf�ｿｽﾌト�ｿｽD�ｿｽ�ｿｽ�ｿｽ[�ｿｽJ�ｿｽ�ｿｽ�ｿｽ[�ｿｽ{�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽO�ｿｽ�ｿｽ�ｿｽ[�ｿｽX�ｿｽP�ｿｽ[�ｿｽ�ｿｽ�ｿｽ{�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@
#if DEF_USE_LIBPNG
			if (!(
				(color_type == 6) ||
				(color_type == 4)
				)) {
				break;
			}
#endif
		}

		// �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌ確�ｿｽ�ｿｽ
		if (pImage == NULL) {
			pImage = (GLubyte*)malloc(sizeof(unsigned char)*size*size * 4);
		}
		if (pImage == NULL) return NULL;
		for (y = 0; y<size; y++){
			pRead = pImage + (size - 1 - y) * 4 * size;
			for (x = 0; x<size; x++) {
				other = 1;
				if (fl == 0) {
					if (isJPEG) {
#if DEF_USE_LIBJPEG
						pRead[0] = jpegimage[size - 1 - y][x * 3];
						pRead[1] = jpegimage[size - 1 - y][x * 3 + 1];
						pRead[2] = jpegimage[size - 1 - y][x * 3 + 2];
						pRead[3] = alpha;				// A
						other = 0;
#endif
					}
					if (isPNG) {
#if DEF_USE_LIBPNG
						if (color_type == 2 || color_type == 6) {
							pRead[0] = pngimage[size - 1 - y][x*pngdepth];
							pRead[1] = pngimage[size - 1 - y][x*pngdepth + 1];
							pRead[2] = pngimage[size - 1 - y][x*pngdepth + 2];
							pRead[3] = alpha;				// A
							if (color_type == 6) {
								pRead[3] = pngimage[size - 1 - y][x*pngdepth + 3];
							}
						}
						other = 0;
#endif
					}
					if (other)  {
						fread(&pRead[2], 1, 1, fp);	// B
						fread(&pRead[1], 1, 1, fp);	// G	
						fread(&pRead[0], 1, 1, fp);	// R
						pRead[3] = alpha;				// A
						if (isTGA && tgah.depth == 32) {
							fread(&pRead[3], 1, 1, fp);	// A
							if (alpha < pRead[3]) pRead[3] = alpha;
						}
					}
				}
				else {
					if (isPNG) {
#if DEF_USE_LIBPNG
						if (color_type == 6) { //�ｿｽg�ｿｽD�ｿｽ�ｿｽ�ｿｽ[�ｿｽJ�ｿｽ�ｿｽ�ｿｽ[�ｿｽ{�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@
							pRead[3] = pngimage[size - 1 - y][x*pngdepth + 3];
						}
						if (color_type == 4) { //�ｿｽO�ｿｽ�ｿｽ�ｿｽ[�ｿｽX�ｿｽP�ｿｽ[�ｿｽ�ｿｽ�ｿｽ{�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@
							pRead[3] = pngimage[size - 1 - y][x*pngdepth + 1];
						}
						if (alpha < pRead[3]) pRead[3] = alpha;
#endif
					}
					if (isTGA) {
						if (tgah.depth == 32) { //�ｿｽ�ｿｽ�ｿｽ�ｿｽﾈゑｿｽ�ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽﾇみ費ｿｽﾎゑｿｽ
							fread(wbuf, 3, 1, fp);	// BGR
						}
						fread(&pRead[3], 1, 1, fp);	// A
						if (alpha < pRead[3]) pRead[3] = alpha;
					}
				}
				pRead += 4;
			}
		}
		fclose(fp);
		fp = NULL;
		}
	if (sts != 0) {
		if (pImage != NULL) free(pImage);
		if (fp != NULL) fclose(fp);
	}
#if DEF_USE_LIBPNG
	if (pngimage != NULL) {
		unsigned int uy;
		for (uy = 0; uy < pngheight; uy++) free(pngimage[uy]);            // �ｿｽﾈ会ｿｽ�ｿｽQ�ｿｽs�ｿｽﾍ２�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ
		free(pngimage);
	}
#endif
#if DEF_USE_LIBJPEG
	if (jpegimage != NULL) {
		unsigned int uy;
		for (uy = 0; uy < cinfo.output_height; uy++) free(jpegimage[uy]);            // �ｿｽﾈ会ｿｽ�ｿｽQ�ｿｽs�ｿｽﾍ２�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜゑｿｽ
		free(jpegimage);
	}
#endif
	if (size < 0) {
		if (pImage != NULL) free(pImage);
		pImage = NULL;
	}
	*tex_size = size;

	return pImage;
	}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoLoadFile
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ�ｿｽ�ｿｽ^�ｿｽZ�ｿｽR�ｿｽC�ｿｽA�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ(*.mqo)�ｿｽ�ｿｽ�ｿｽ�ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
mqoobj		MQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg
filename	�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾌパ�ｿｽX
scale		�ｿｽg�ｿｽ蝸ｦ
alpha		�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽF1 �ｿｽ^ �ｿｽ�ｿｽ�ｿｽs�ｿｽF0
=========================================================================*/

int mqoLoadFile(MQO_OBJECT *mqoobj, char *filename, double scale, unsigned char alpha)
{
	FILE			*fp;
	MQO_OBJDATA		obj[MAX_OBJECT];
	MQO_MATDATA		*M = NULL;

	char	buf[SIZE_STR];		// �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽﾝバ�ｿｽb�ｿｽt�ｿｽ@
	char	path_dir[SIZE_STR];	// �ｿｽf�ｿｽB�ｿｽ�ｿｽ�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽﾌパ�ｿｽX
	char	path_tex[SIZE_STR];	// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾌパ�ｿｽX
	char	path_alp[SIZE_STR];	// �ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾌパ�ｿｽX
	int		n_mat = 0;			// �ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ
	int		n_obj = 0;			// �ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽ
	int		i;
	errno_t err;

	// Material�ｿｽ�ｿｽObject�ｿｽﾌ読み搾ｿｽ�ｿｽ�ｿｽ
#if _MSC_VER >=1400
	err = fopen_s(&fp, filename, "rb");
	if (err != 0) return 0;
#else
	fp = fopen(filename, "rb");
	if (fp == NULL) return 0;
#endif

	mqoobj->alpha = alpha;
	memset(obj, 0, sizeof(obj));

	i = 0;
	while (!feof(fp)) {
		fgets(buf, SIZE_STR, fp);

		// Material
		if (strstr(buf, "Material")) {
			sscanf(buf, "Material %d", &n_mat);
			M = (MQO_MATDATA*)calloc(n_mat, sizeof(MQO_MATDATA));
			mqoReadMaterial(fp, M);
		}

		// Object
		if (strstr(buf, "Object")) {
			sscanf(buf, "Object %s", obj[i].objname);
			mqoReadObject(fp, &obj[i]);
			i++;
		}
	}
	n_obj = i;
	fclose(fp);

	// �ｿｽp�ｿｽX�ｿｽﾌ取得
	mqoGetDirectory(filename, path_dir);

	// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾌ登�ｿｽ^
	for (i = 0; i<n_mat; i++) {
		if (M[i].useTex) {

			if (strstr(M[i].texFile, ":")) {
				strcpy(path_tex, M[i].texFile);	// �ｿｽ�ｿｽﾎパ�ｿｽX�ｿｽﾌ場合
			}
			else {
				sprintf(path_tex, "%s%s", path_dir, M[i].texFile);	// �ｿｽ�ｿｽ�ｿｽﾎパ�ｿｽX�ｿｽﾌ場合
			}

			if (M[i].alpFile[0] != (char)0) {
				if (strstr(M[i].texFile, ":")) {
					strcpy(path_alp, M[i].alpFile);	// �ｿｽ�ｿｽﾎパ�ｿｽX�ｿｽﾌ場合
				}
				else {
					sprintf(path_alp, "%s%s", path_dir, M[i].alpFile);	// �ｿｽ�ｿｽ�ｿｽﾎパ�ｿｽX�ｿｽﾌ場合
				}
				M[i].texName = mqoSetTexturePool(path_tex, path_alp, alpha);
			}
			else {
				M[i].texName = mqoSetTexturePool(path_tex, NULL, alpha);
			}
		}
	}

	mqoMakeObjectsEx(mqoobj, obj, n_obj, M, n_mat, scale, alpha);

	// �ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽﾌデ�ｿｽ[�ｿｽ^�ｿｽﾌ開�ｿｽ�ｿｽ
	for (i = 0; i<n_obj; i++) {
		free(obj[i].V);
		free(obj[i].F);
	}

	// �ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽﾌ開�ｿｽ�ｿｽ
	free(M);

	return 1;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoCreateList
�ｿｽy�ｿｽp�ｿｽr�ｿｽzMQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽw�ｿｽ關費ｿｽm�ｿｽﾛゑｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽznum		MQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽﾌ撰ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽzMQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg
=========================================================================*/

MQO_OBJECT* mqoCreateList(int num)
{
	MQO_OBJECT *obj;

	// �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄなゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ迴会ｿｽ�ｿｽ�ｿｽ�ｿｽ
	if (!l_GLMetaseqInitialized) mqoInit();

	// �ｿｽﾌ茨ｿｽm�ｿｽﾛと擾ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
	obj = (MQO_OBJECT *)malloc(sizeof(MQO_OBJECT)*num);
	memset(obj, 0, sizeof(MQO_OBJECT)*num);

	return obj;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoCreateListObject
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ�ｿｽ�ｿｽ^�ｿｽZ�ｿｽR�ｿｽC�ｿｽA�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ(*.mqo)�ｿｽ�ｿｽ�ｿｽ�ｿｽMQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽz�ｿｽ�ｿｽ�ｿｽ�ｿｽ�成�ｿｽ�ｿｽ�ｿｽ�ｿｽ

�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽzmqoobj		MQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg
i			�ｿｽﾇみ搾ｿｽ�ｿｽﾝ撰ｿｽﾔ搾ｿｽ�ｿｽii�ｿｽﾔ目ゑｿｽMQO�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽﾞ）
filename	�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾌパ�ｿｽX
scale		�ｿｽg�ｿｽ蝸ｦ
alpha		�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽw�ｿｽ�ｿｽi�ｿｽS�ｿｽﾌのア�ｿｽ�ｿｽ�ｿｽt�ｿｽ@�ｿｽl�ｿｽ�ｿｽ�ｿｽw�ｿｽ�ｿｽi0�ｿｽ`255�ｿｽj�ｿｽj

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽX�ｿｽe�ｿｽ[�ｿｽ^�ｿｽX�ｿｽ@�ｿｽ�ｿｽ�ｿｽF�ｿｽﾙ擾ｿｽ@�ｿｽO�ｿｽF�ｿｽ�ｿｽ�ｿｽ�ｿｽ
=========================================================================*/

int mqoCreateListObject(MQO_OBJECT *mqoobj, int i, char *filename, double scale, unsigned char alpha)
{
	int ret;
	ret = 0;
	if (mqoobj == (MQO_OBJECT *)NULL) return -1;
	if (!mqoLoadFile(&mqoobj[i], filename, scale, alpha)) ret = -1;
	return ret;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoCallListObject
�ｿｽy�ｿｽp�ｿｽr�ｿｽzMQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽOpenGL�ｿｽﾌ会ｿｽﾊ擾ｿｽﾉ呼び出�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
mqoobj		MQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽz�ｿｽ�ｿｽ
num			�ｿｽz�ｿｽ�ｿｽﾔ搾ｿｽ (0�ｿｽ`�ｿｽj

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void mqoCallListObject(MQO_OBJECT mqoobj[], int num)
{

	MQO_INNER_OBJECT	*obj;
	MQO_MATERIAL		*mat;
	GLfloat				matenv[4];
	GLint				bindGL_TEXTURE_2D = 0;
	GLboolean			isGL_TEXTURE_2D = GL_FALSE;
	GLboolean			isGL_BLEND = GL_FALSE;
	GLint				blendGL_SRC_ALPHA = 0;
	GLint				intFrontFace;

	int		o, m, offset;
	double	dalpha;
	char	*base;

	if (mqoobj == NULL) return;

	glPushMatrix();
	//�ｿｽ�ｿｽ�ｿｽ^�ｿｽZ�ｿｽR�ｿｽﾍ抵ｿｽ�ｿｽ_�ｿｽﾌ包ｿｽ�ｿｽﾑゑｿｽ�ｿｽ\�ｿｽﾊゑｿｽ�ｿｽ�ｿｽﾝて右�ｿｽ�ｿｽ�ｿｽ
	glGetIntegerv(GL_FRONT_FACE, &intFrontFace);
	glFrontFace(GL_CW);
	dalpha = (double)mqoobj[num].alpha / (double)255;

	for (o = 0; o<mqoobj[num].objnum; o++) {	// �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ[�ｿｽv

		obj = &mqoobj[num].obj[o];
		if (!obj->isVisible) continue;
		glShadeModel(((obj->isShadingFlat)) ? GL_FLAT : GL_SMOOTH);

		for (m = 0; m < obj->matnum; m++) {	//�ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ[�ｿｽv

			mat = &obj->mat[m];
			if (mat->datanum == 0) continue;

			if (mat->isValidMaterialInfo) {	// �ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽﾌ擾ｿｽ�ｿｽﾝ抵ｿｽ
				memcpy(matenv, mat->dif, sizeof(matenv));
				matenv[3] *= dalpha;
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matenv);
				memcpy(matenv, mat->amb, sizeof(matenv));
				matenv[3] *= dalpha;
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matenv);
				memcpy(matenv, mat->spc, sizeof(matenv));
				matenv[3] *= dalpha;
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matenv);
				memcpy(matenv, mat->emi, sizeof(matenv));
				matenv[3] *= dalpha;
				glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matenv);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat->power);
			}

			if (mat->isUseTexture) {	// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ鼾�
				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);

				isGL_TEXTURE_2D = glIsEnabled(GL_TEXTURE_2D);
				isGL_BLEND = glIsEnabled(GL_BLEND);
				glGetIntegerv(GL_TEXTURE_BINDING_2D, &bindGL_TEXTURE_2D);
				//					glGetIntegerv(GL_BLEND_SRC_ALPHA,&blendGL_SRC_ALPHA);

				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glBindTexture(GL_TEXTURE_2D, mat->texture_id);

				if (g_isVBOSupported) {	// �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽg�ｿｽp
					base = (char *)NULL;	// �ｿｽA�ｿｽh�ｿｽ�ｿｽ�ｿｽX�ｿｽ�ｿｽNULL�ｿｽ�ｿｽ�ｿｽ謫ｪ
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, mat->VBO_id); // �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾑつゑｿｽ�ｿｽ�ｿｽ
				}
				else {
					// �ｿｽ�ｿｽ�ｿｽ_�ｿｽz�ｿｽ�ｿｽﾌ趣ｿｽ�ｿｽﾍ、�ｿｽA�ｿｽh�ｿｽ�ｿｽ�ｿｽX�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌまま難ｿｽ�ｿｽ�ｿｽ�ｿｽ
					base = (char *)mat->vertex_t[0].point;
				}

				// �ｿｽ�ｿｽ�ｿｽ_�ｿｽz�ｿｽ�ｿｽ�ｿｽﾝ抵ｿｽ
				offset = (int)((char *)mat->vertex_t[0].point - (char *)mat->vertex_t[0].point);
				glVertexPointer(3, GL_FLOAT, sizeof(VERTEX_TEXUSE), base + offset);

				// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽW�ｿｽz�ｿｽ�ｿｽ�ｿｽﾝ抵ｿｽ
				offset = (int)((char *)mat->vertex_t[0].uv - (char *)mat->vertex_t[0].point);
				glTexCoordPointer(2, GL_FLOAT, sizeof(VERTEX_TEXUSE), base + offset);

				// �ｿｽ@�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ�ｿｽﾝ抵ｿｽ
				offset = (int)((char *)mat->vertex_t[0].normal - (char *)mat->vertex_t[0].point);
				glNormalPointer(GL_FLOAT, sizeof(VERTEX_TEXUSE), base + offset);

				// �ｿｽF�ｿｽﾝ抵ｿｽ
				glColor4f(mat->color[0], mat->color[1], mat->color[2], mat->color[3]);

				// �ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽs
				glDrawArrays(GL_TRIANGLES, 0, mat->datanum);

				glBindTexture(GL_TEXTURE_2D, bindGL_TEXTURE_2D);
				if (isGL_BLEND == GL_FALSE) glDisable(GL_BLEND);
				if (isGL_TEXTURE_2D == GL_FALSE) glDisable(GL_TEXTURE_2D);

				if (g_isVBOSupported) {						// �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽg�ｿｽp
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);	// �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽ�ｿｽ�ｿｽf�ｿｽt�ｿｽH�ｿｽ�ｿｽ�ｿｽg�ｿｽ�ｿｽ
				}

				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			}
			else {	// �ｿｽe�ｿｽN�ｿｽX�ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾈゑｿｽ�ｿｽ鼾�

				glEnableClientState(GL_VERTEX_ARRAY);
				glEnableClientState(GL_NORMAL_ARRAY);
				//	glEnableClientState( GL_COLOR_ARRAY );

				isGL_BLEND = glIsEnabled(GL_BLEND);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				if (g_isVBOSupported) {	// �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽg�ｿｽp
					base = (char *)NULL;
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, mat->VBO_id);
				}
				else {
					base = (char *)mat->vertex_p[0].point;
				}

				// �ｿｽ�ｿｽ�ｿｽ_�ｿｽz�ｿｽ�ｿｽ�ｿｽﾝ抵ｿｽ
				offset = (int)((char *)mat->vertex_p[0].point - (char *)mat->vertex_p[0].point);
				glVertexPointer(3, GL_FLOAT, sizeof(VERTEX_NOTEX), base + offset);

				// �ｿｽ@�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ�ｿｽﾝ抵ｿｽ
				offset = (int)((char *)mat->vertex_p[0].normal - (char *)mat->vertex_p[0].point);
				glNormalPointer(GL_FLOAT, sizeof(VERTEX_NOTEX), base + offset);

				// �ｿｽF�ｿｽﾝ抵ｿｽ
				glColor4f(mat->color[0], mat->color[1], mat->color[2], mat->color[3]);
				//	offset = (int)((char *)mat->vertex_p[0].color-(char *)mat->vertex_p[0].point);
				//	glColorPointer(4,GL_FLOAT,sizeof(VERTEX_NOTEX),base+offset);

				// �ｿｽ`�ｿｽ�ｿｽ�ｿｽ�ｿｽs
				glDrawArrays(GL_TRIANGLES, 0, mat->datanum);

				if (isGL_BLEND == GL_FALSE) glDisable(GL_BLEND);
				if (g_isVBOSupported) {						// �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽg�ｿｽp
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);	// �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽ�ｿｽ�ｿｽf�ｿｽt�ｿｽH�ｿｽ�ｿｽ�ｿｽg�ｿｽ�ｿｽ
				}

				//	glDisableClientState( GL_COLOR_ARRAY );
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_NORMAL_ARRAY);

			}
		}
	}

	//�ｿｽ�ｿｽ�ｿｽ^�ｿｽZ�ｿｽR�ｿｽﾍ抵ｿｽ�ｿｽ_�ｿｽﾌ包ｿｽ�ｿｽﾑゑｿｽ�ｿｽ\�ｿｽﾊゑｿｽ�ｿｽ�ｿｽﾝて右�ｿｽ�ｿｽ�ｿｽi�ｿｽ�ｿｽ�ｿｽﾌ設抵ｿｽﾉゑｿｽ�ｿｽﾇゑｿｽ�ｿｽj
	glFrontFace(intFrontFace);
	glPopMatrix();
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoGetDirectory
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜむパ�ｿｽX�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽｩゑｿｽf�ｿｽB�ｿｽ�ｿｽ�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽﾌパ�ｿｽX�ｿｽﾌみを抽出�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
*path_file	�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾜむパ�ｿｽX�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽi�ｿｽ�ｿｽ�ｿｽﾍ）
*path_dir	�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽp�ｿｽX�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽi�ｿｽo�ｿｽﾍ）

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽz�ｿｽ�ｿｽF
"C:/data/file.bmp" �ｿｽ�ｿｽ "C:/data/"
"data/file.mqo"    �ｿｽ�ｿｽ "data/"
=========================================================================*/

void mqoGetDirectory(const char *path_file, char *path_dir)
{
	char *pStr;
	int len;

	pStr = MAX(strrchr(path_file, '\\'), strrchr(path_file, '/'));
	len = MAX((int)(pStr - path_file) + 1, 0);
	strncpy(path_dir, path_file, len);
	path_dir[len] = (char)0;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoSnormal
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ@�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾟゑｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
A		3�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽW�ｿｽ�ｿｽﾌ点A
B		3�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽW�ｿｽ�ｿｽﾌ点B
C		3�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽW�ｿｽ�ｿｽﾌ点C
*normal	�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽBA�ｿｽﾆベ�ｿｽN�ｿｽg�ｿｽ�ｿｽBC�ｿｽﾌ法�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽi�ｿｽE�ｿｽﾋゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽj

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽz�ｿｽ�ｿｽ�ｿｽ^�ｿｽZ�ｿｽR�ｿｽC�ｿｽA�ｿｽﾉゑｿｽ�ｿｽ�ｿｽ�ｿｽﾄ面ゑｿｽ�ｿｽ\�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ髓ｸ�ｿｽ_�ｿｽﾌ番搾ｿｽ�ｿｽﾍ，�ｿｽ\�ｿｽ�ｿｽ�ｿｽﾊゑｿｽ�ｿｽ迪ｩ�ｿｽ�ｿｽ
�ｿｽ�ｿｽ�ｿｽv�ｿｽ�ｿｽ�ｿｽﾉ記�ｿｽq�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ�ｿｽD�ｿｽﾂまゑｿｽC�ｿｽ�ｿｽ�ｿｽ_A,B,C �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾆゑｿｽ�ｿｽC
�ｿｽ�ｿｽ�ｿｽﾟゑｿｽﾗゑｿｽ�ｿｽ@�ｿｽ�ｿｽ�ｿｽ�ｿｽBA�ｿｽ�ｿｽBC�ｿｽﾌ外�ｿｽﾏにゑｿｽ�ｿｽ�ｿｽﾄ具ｿｽ�ｿｽﾟゑｿｽ�ｿｽ�ｿｽ
=========================================================================*/

void mqoSnormal(glPOINT3f A, glPOINT3f B, glPOINT3f C, glPOINT3f *normal)
{
	double norm;
	glPOINT3f vec0, vec1;

	// �ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽBA
	vec0.x = A.x - B.x;
	vec0.y = A.y - B.y;
	vec0.z = A.z - B.z;

	// �ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽBC
	vec1.x = C.x - B.x;
	vec1.y = C.y - B.y;
	vec1.z = C.z - B.z;

	// �ｿｽ@�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ
	normal->x = vec0.y * vec1.z - vec0.z * vec1.y;
	normal->y = vec0.z * vec1.x - vec0.x * vec1.z;
	normal->z = vec0.x * vec1.y - vec0.y * vec1.x;

	// �ｿｽ�ｿｽ�ｿｽK�ｿｽ�ｿｽ
	norm = normal->x * normal->x + normal->y * normal->y + normal->z * normal->z;
	norm = sqrt(norm);

	normal->x /= norm;
	normal->y /= norm;
	normal->z /= norm;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoReadMaterial
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌ読み搾ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
fp		�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ|�ｿｽC�ｿｽ�ｿｽ�ｿｽ^
M		�ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽzmqoCreateModel(), mqoCreateSequence()�ｿｽﾌサ�ｿｽu�ｿｽﾖ撰ｿｽ�ｿｽD
=========================================================================*/

void mqoReadMaterial(FILE *fp, MQO_MATDATA M[])
{
	GLfloat		dif, amb, emi, spc;
	glCOLOR4f	c;
	char		buf[SIZE_STR];
	char		*pStrEnd, *pStr;
	int			len;
	int			i = 0;

	while (1) {
		fgets(buf, SIZE_STR, fp);	// �ｿｽs�ｿｽﾇみ搾ｿｽ�ｿｽ�ｿｽ
		if (strstr(buf, "}")) break;

		pStr = strstr(buf, "col(");	// �ｿｽﾞ趣ｿｽ�ｿｽ�ｿｽ�ｿｽﾇみ費ｿｽﾎゑｿｽ
		sscanf(pStr,
			"col(%f %f %f %f) dif (%f) amb(%f) emi(%f) spc(%f) power(%f)",
			&c.r, &c.g, &c.b, &c.a, &dif, &amb, &emi, &spc, &M[i].power);

		// �ｿｽ�ｿｽ�ｿｽ_�ｿｽJ�ｿｽ�ｿｽ�ｿｽ[
		M[i].col = c;

		// �ｿｽg�ｿｽU�ｿｽ�ｿｽ
		M[i].dif[0] = dif * c.r;
		M[i].dif[1] = dif * c.g;
		M[i].dif[2] = dif * c.b;
		M[i].dif[3] = c.a;

		// �ｿｽ�ｿｽ�ｿｽﾍ鯉ｿｽ
		M[i].amb[0] = amb * c.r;
		M[i].amb[1] = amb * c.g;
		M[i].amb[2] = amb * c.b;
		M[i].amb[3] = c.a;

		// �ｿｽ�ｿｽ�ｿｽﾈ照厄ｿｽ
		M[i].emi[0] = emi * c.r;
		M[i].emi[1] = emi * c.g;
		M[i].emi[2] = emi * c.b;
		M[i].emi[3] = c.a;

		// �ｿｽ�ｿｽ�ｿｽﾋ鯉ｿｽ
		M[i].spc[0] = spc * c.r;
		M[i].spc[1] = spc * c.g;
		M[i].spc[2] = spc * c.b;
		M[i].spc[3] = c.a;

		// tex�ｿｽF�ｿｽﾍ様�ｿｽ}�ｿｽb�ｿｽs�ｿｽ�ｿｽ�ｿｽO�ｿｽ�ｿｽ
		if ((pStr = strstr(buf, "tex(")) != NULL) {
			M[i].useTex = TRUE;

			pStrEnd = strstr(pStr, ")") - 1;
			len = pStrEnd - (pStr + 5);
			strncpy(M[i].texFile, pStr + 5, len);
			M[i].texFile[len] = (char)0;
			if ((pStr = strstr(buf, "aplane(")) != NULL) {
				pStrEnd = strstr(pStr, ")") - 1;
				len = pStrEnd - (pStr + 8);
				strncpy(M[i].alpFile, pStr + 8, len);
				M[i].alpFile[len] = (char)0;
			}
			else {
				M[i].alpFile[0] = (char)0;
			}

		}
		else {
			M[i].useTex = FALSE;
			M[i].texFile[0] = (char)0;
			M[i].alpFile[0] = (char)0;
		}

		i++;
	}

}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoReadVertex
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ�ｿｽ�ｿｽ_�ｿｽ�ｿｽ�ｿｽﾌ読み搾ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
fp		�ｿｽ�ｿｽ�ｿｽﾝオ�ｿｽ[�ｿｽv�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ驛��ｿｽ^�ｿｽZ�ｿｽR�ｿｽC�ｿｽA�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾌフ�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ|�ｿｽC�ｿｽ�ｿｽ�ｿｽ^
V		�ｿｽ�ｿｽ�ｿｽ_�ｿｽ�ｿｽ�ｿｽi�ｿｽ[�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽzmqoReadObject()�ｿｽﾌサ�ｿｽu�ｿｽﾖ撰ｿｽ
=========================================================================*/

void mqoReadVertex(FILE *fp, glPOINT3f V[])
{
	char buf[SIZE_STR];
	int  i = 0;

	while (1) {
		fgets(buf, SIZE_STR, fp);
		if (strstr(buf, "}")) break;
		sscanf(buf, "%f %f %f", &V[i].x, &V[i].y, &V[i].z);
		i++;
	}
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoReadBVertex
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽo�ｿｽC�ｿｽi�ｿｽ�ｿｽ�ｿｽ`�ｿｽ�ｿｽ�ｿｽﾌ抵ｿｽ�ｿｽ_�ｿｽ�ｿｽ�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
fp		�ｿｽ�ｿｽ�ｿｽﾝオ�ｿｽ[�ｿｽv�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ驛��ｿｽ^�ｿｽZ�ｿｽR�ｿｽC�ｿｽA�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾌフ�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ|�ｿｽC�ｿｽ�ｿｽ�ｿｽ^
V		�ｿｽ�ｿｽ�ｿｽ_�ｿｽ�ｿｽ�ｿｽi�ｿｽ[�ｿｽ�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽ�ｿｽ�ｿｽ_�ｿｽ�ｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽzmqoReadObject()�ｿｽﾌサ�ｿｽu�ｿｽﾖ撰ｿｽ
=========================================================================*/

int mqoReadBVertex(FILE *fp, glPOINT3f V[])
{
	int n_vertex, i;
	float *wf;
	int size;
	char cw[256];
	char *pStr;

	fgets(cw, sizeof(cw), fp);
	if ((pStr = strstr(cw, "Vector")) != NULL) {
		sscanf(pStr, "Vector %d [%d]", &n_vertex, &size);	// �ｿｽ�ｿｽ�ｿｽ_�ｿｽ�ｿｽ�ｿｽA�ｿｽf�ｿｽ[�ｿｽ^�ｿｽT�ｿｽC�ｿｽY�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽ�ｿｽ
	}
	else {
		return -1;
	}
	//MQO�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾌバ�ｿｽC�ｿｽi�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ_�ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽintel�ｿｽ`�ｿｽ�ｿｽ�ｿｽi�ｿｽ�ｿｽ�ｿｽg�ｿｽ�ｿｽ�ｿｽG�ｿｽf�ｿｽB�ｿｽA�ｿｽ�ｿｽ�ｿｽj
	wf = (float *)malloc(size);
	fread(wf, size, 1, fp);
	for (i = 0; i < n_vertex; i++) {
		V[i].x = wf[i * 3 + 0];
		V[i].y = wf[i * 3 + 1];
		V[i].z = wf[i * 3 + 2];
#if DEF_IS_LITTLE_ENDIAN
#else
		endianConverter((void *)&V[i].x, sizeof(V[i].x));
		endianConverter(&V[i].y, sizeof(V[i].y));
		endianConverter(&V[i].z, sizeof(V[i].z));
#endif
	}
	free(wf);

	// "}"�ｿｽﾜで読み費ｿｽﾎゑｿｽ
	{
		char buf[SIZE_STR];
		while (1) {
			fgets(buf, SIZE_STR, fp);
			if (strstr(buf, "}")) break;
		}
	}

	return n_vertex;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoReadFace
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽﾊ擾ｿｽ�ｿｽﾌ読み搾ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
fp		�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ|�ｿｽC�ｿｽ�ｿｽ�ｿｽ^
F		�ｿｽﾊ配�ｿｽ�ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽzmqoReadObject()�ｿｽﾌサ�ｿｽu�ｿｽﾖ撰ｿｽ
=========================================================================*/

void mqoReadFace(FILE *fp, MQO_FACE F[])
{
	char buf[SIZE_STR];
	char *pStr;
	int  i = 0;

	while (1) {
		fgets(buf, SIZE_STR, fp);
		if (strstr(buf, "}")) break;

		// �ｿｽﾊゑｿｽ�ｿｽ\�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ髓ｸ�ｿｽ_�ｿｽ�ｿｽ
		sscanf(buf, "%d", &F[i].n);

		// �ｿｽ�ｿｽ�ｿｽ_(V)�ｿｽﾌ読み搾ｿｽ�ｿｽ�ｿｽ
		if ((pStr = strstr(buf, "V(")) != NULL) {
			switch (F[i].n) {
			case 3:
				//�ｿｽ�ｿｽ�ｿｽ^�ｿｽZ�ｿｽR�ｿｽﾍ抵ｿｽ�ｿｽ_�ｿｽﾌ包ｿｽ�ｿｽﾑゑｿｽ�ｿｽ\�ｿｽﾊゑｿｽ�ｿｽ�ｿｽﾝて右�ｿｽ�ｿｽ�ｿｽ
				//�ｿｽﾇみ搾ｿｽ�ｿｽﾝ趣ｿｽ�ｿｽﾉ包ｿｽ�ｿｽﾗ替ゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ@�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽB�ｿｽ�ｿｽ�ｿｽﾇ、�ｿｽ\�ｿｽﾊの設抵ｿｽ�ｿｽ
				//glFrontFace�ｿｽﾅ変ゑｿｽ�ｿｽ�ｿｽﾙゑｿｽ�ｿｽ�ｿｽ�ｿｽX�ｿｽ}�ｿｽ[�ｿｽg�ｿｽH
				sscanf(pStr, "V(%d %d %d)", &F[i].v[0], &F[i].v[1], &F[i].v[2]);
				//					sscanf(pStr,"V(%d %d %d)",&F[i].v[2],&F[i].v[1],&F[i].v[0]);
				break;
			case 4:
				sscanf(pStr, "V(%d %d %d %d)", &F[i].v[0], &F[i].v[1], &F[i].v[2], &F[i].v[3]);
				//					sscanf(pStr,"V(%d %d %d %d)",&F[i].v[3],&F[i].v[2],&F[i].v[1],&F[i].v[0]);
				break;
			default:
				break;
			}
		}

		// �ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ(M)�ｿｽﾌ読み搾ｿｽ�ｿｽ�ｿｽ
		F[i].m = 0;
		if ((pStr = strstr(buf, "M(")) != NULL) {
			sscanf(pStr, "M(%d)", &F[i].m);
		}
		else { // �ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾝ定さ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽﾈゑｿｽ�ｿｽ�ｿｽ
			F[i].m = -1;
		}

		// UV�ｿｽ}�ｿｽb�ｿｽv(UV)�ｿｽﾌ読み搾ｿｽ�ｿｽ�ｿｽ
		if ((pStr = strstr(buf, "UV(")) != NULL) {
			switch (F[i].n) {
			case 3:	// �ｿｽ�ｿｽ�ｿｽ_�ｿｽ�ｿｽ3
				sscanf(pStr, "UV(%f %f %f %f %f %f)",
					&F[i].uv[0].x, &F[i].uv[0].y,
					&F[i].uv[1].x, &F[i].uv[1].y,
					&F[i].uv[2].x, &F[i].uv[2].y
					);
				break;

			case 4:	// �ｿｽ�ｿｽ�ｿｽ_�ｿｽ�ｿｽ4
				sscanf(pStr, "UV(%f %f %f %f %f %f %f %f)",
					&F[i].uv[0].x, &F[i].uv[0].y,
					&F[i].uv[1].x, &F[i].uv[1].y,
					&F[i].uv[2].x, &F[i].uv[2].y,
					&F[i].uv[3].x, &F[i].uv[3].y
					);
				break;
			default:
				break;
			}
		}

		i++;
	}

}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoReadObject
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽﾌ読み搾ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
fp		�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ|�ｿｽC�ｿｽ�ｿｽ�ｿｽ^
obj		�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽz�ｿｽ�ｿｽ�ｿｽﾌ関撰ｿｽ�ｿｽﾅ１�ｿｽﾂのオ�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽｪ読み搾ｿｽ�ｿｽﾜゑｿｽ�ｿｽD
=========================================================================*/

void mqoReadObject(FILE *fp, MQO_OBJDATA *obj)
{
	char buf[SIZE_STR];

	while (1) {
		fgets(buf, SIZE_STR, fp);
		if (strstr(buf, "}")) break;

		// visible
		if (strstr(buf, "visible ")) {
			sscanf(buf, " visible %d", &obj->visible);
		}

		// shading
		if (strstr(buf, "shading ")) {
			sscanf(buf, " shading %d", &obj->shading);
		}

		// facet
		if (strstr(buf, "facet ")) {
			sscanf(buf, " facet %f", &obj->facet);
		}

		// vertex
		if (strstr(buf, "vertex ")) {
			sscanf(buf, " vertex %d", &obj->n_vertex);
			obj->V = (glPOINT3f*)calloc(obj->n_vertex, sizeof(glPOINT3f));
			mqoReadVertex(fp, obj->V);
		}
		// BVertex
		if (strstr(buf, "BVertex"))	{
			sscanf(buf, " BVertex %d", &obj->n_vertex);
			obj->V = (glPOINT3f*)calloc(obj->n_vertex, sizeof(glPOINT3f));
			mqoReadBVertex(fp, obj->V);
		}

		// face
		if (strstr(buf, "face ")) {
			sscanf(buf, " face %d", &obj->n_face);
			obj->F = (MQO_FACE*)calloc(obj->n_face, sizeof(MQO_FACE));
			mqoReadFace(fp, obj->F);
		}

	}

}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoMakeArray
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ�ｿｽ�ｿｽ_�ｿｽz�ｿｽ�ｿｽﾌ作成
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
mat		�ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽi�ｿｽ�ｿｽ�ｿｽﾌ抵ｿｽ�ｿｽﾉ抵ｿｽ�ｿｽ_�ｿｽf�ｿｽ[�ｿｽ^�ｿｽ�ｿｽ�ｿｽﾜむ）
matpos	�ｿｽﾞ趣ｿｽ�ｿｽﾔ搾ｿｽ
F		�ｿｽ�ｿｽ
fnum	�ｿｽﾊ撰ｿｽ
V		�ｿｽ�ｿｽ�ｿｽ_
N		�ｿｽ@�ｿｽ�ｿｽ
facet	�ｿｽX�ｿｽ�ｿｽ�ｿｽ[�ｿｽW�ｿｽ�ｿｽ�ｿｽO�ｿｽp
mcol	�ｿｽF
scale	�ｿｽX�ｿｽP�ｿｽ[�ｿｽ�ｿｽ
alpha	�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽz�ｿｽ�ｿｽ�ｿｽ_�ｿｽz�ｿｽ�ｿｽﾍゑｿｽ�ｿｽﾗて三�ｿｽp�ｿｽﾉゑｿｽ�ｿｽ�ｿｽﾌで、�ｿｽl�ｿｽp�ｿｽﾍ三�ｿｽp�ｿｽ�ｿｽ�ｿｽQ�ｿｽﾉ包ｿｽ�ｿｽ�ｿｽ
0  3      0    0  3
�ｿｽ�ｿｽ   �ｿｽ�ｿｽ�ｿｽ@�ｿｽ�ｿｽ�ｿｽ@�ｿｽ@�ｿｽ�ｿｽ
1  2     1  2   2
=========================================================================*/

void mqoMakeArray(MQO_MATERIAL *mat, int matpos, MQO_FACE F[], int fnum, glPOINT3f V[],
	glPOINT3f N[], double facet, glCOLOR4f *mcol, double scale, unsigned char alpha)
{
	int f;
	int i;
	int dpos;
	double s;
	glPOINT3f normal;	// �ｿｽ@�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ

	dpos = 0;
	mat->color[0] = mcol->r;
	mat->color[1] = mcol->g;
	mat->color[2] = mcol->b;
	mat->color[3] = mcol->a;
	if (mat->isUseTexture) {
		for (f = 0; f < fnum; f++){
			if (F[f].m != matpos) continue;
			if (F[f].n == 3) {
				mqoSnormal(V[F[f].v[0]], V[F[f].v[1]], V[F[f].v[2]], &normal);	// �ｿｽ@�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽv�ｿｽZ
				for (i = 0; i < 3; i++) {
					mat->vertex_t[dpos].point[0] = V[F[f].v[i]].x*scale;
					mat->vertex_t[dpos].point[1] = V[F[f].v[i]].y*scale;
					mat->vertex_t[dpos].point[2] = V[F[f].v[i]].z*scale;
					mat->vertex_t[dpos].uv[0] = F[f].uv[i].x;
					mat->vertex_t[dpos].uv[1] = F[f].uv[i].y;
					s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
					if (facet < s) {
						// �ｿｽX�ｿｽ�ｿｽ�ｿｽ[�ｿｽW�ｿｽ�ｿｽ�ｿｽO�ｿｽp�ｿｽ@�ｿｽ�ｿｽ�ｿｽi�ｿｽ�ｿｽ�ｿｽ_�ｿｽ@�ｿｽ�ｿｽ�ｿｽﾆ面法�ｿｽ�ｿｽ�ｿｽﾌ角�ｿｽx�ｿｽj�ｿｽﾌとゑｿｽ�ｿｽﾍ面法�ｿｽ�ｿｽ�ｿｽｸ点�ｿｽ@�ｿｽ�ｿｽ�ｿｽﾆゑｿｽ�ｿｽ�ｿｽ
						mat->vertex_t[dpos].normal[0] = normal.x;
						mat->vertex_t[dpos].normal[1] = normal.y;
						mat->vertex_t[dpos].normal[2] = normal.z;
					}
					else {
						mat->vertex_t[dpos].normal[0] = N[F[f].v[i]].x;
						mat->vertex_t[dpos].normal[1] = N[F[f].v[i]].y;
						mat->vertex_t[dpos].normal[2] = N[F[f].v[i]].z;
					}
					dpos++;
				}
			}
			//�ｿｽS�ｿｽ�ｿｽ�ｿｽ_�ｿｽi�ｿｽl�ｿｽp�ｿｽj�ｿｽﾍ３�ｿｽ�ｿｽ�ｿｽ_�ｿｽi�ｿｽO�ｿｽp�ｿｽj�ｿｽ�ｿｽ�ｿｽQ�ｿｽﾉ包ｿｽ�ｿｽ�ｿｽ
			if (F[f].n == 4) {
				mqoSnormal(V[F[f].v[0]], V[F[f].v[1]], V[F[f].v[2]], &normal);	// �ｿｽ@�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽv�ｿｽZ
				for (i = 0; i < 4; i++) {
					if (i == 3) continue;
					mat->vertex_t[dpos].point[0] = V[F[f].v[i]].x*scale;
					mat->vertex_t[dpos].point[1] = V[F[f].v[i]].y*scale;
					mat->vertex_t[dpos].point[2] = V[F[f].v[i]].z*scale;
					mat->vertex_t[dpos].uv[0] = F[f].uv[i].x;
					mat->vertex_t[dpos].uv[1] = F[f].uv[i].y;
					s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
					if (facet < s) {
						mat->vertex_t[dpos].normal[0] = normal.x;
						mat->vertex_t[dpos].normal[1] = normal.y;
						mat->vertex_t[dpos].normal[2] = normal.z;
					}
					else {
						mat->vertex_t[dpos].normal[0] = N[F[f].v[i]].x;
						mat->vertex_t[dpos].normal[1] = N[F[f].v[i]].y;
						mat->vertex_t[dpos].normal[2] = N[F[f].v[i]].z;
					}
					dpos++;
				}
				mqoSnormal(V[F[f].v[0]], V[F[f].v[2]], V[F[f].v[3]], &normal);	// �ｿｽ@�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽv�ｿｽZ
				for (i = 0; i < 4; i++) {
					if (i == 1) continue;
					mat->vertex_t[dpos].point[0] = V[F[f].v[i]].x*scale;
					mat->vertex_t[dpos].point[1] = V[F[f].v[i]].y*scale;
					mat->vertex_t[dpos].point[2] = V[F[f].v[i]].z*scale;
					mat->vertex_t[dpos].uv[0] = F[f].uv[i].x;
					mat->vertex_t[dpos].uv[1] = F[f].uv[i].y;
					s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
					if (facet < s) {
						mat->vertex_t[dpos].normal[0] = normal.x;
						mat->vertex_t[dpos].normal[1] = normal.y;
						mat->vertex_t[dpos].normal[2] = normal.z;
					}
					else {
						mat->vertex_t[dpos].normal[0] = N[F[f].v[i]].x;
						mat->vertex_t[dpos].normal[1] = N[F[f].v[i]].y;
						mat->vertex_t[dpos].normal[2] = N[F[f].v[i]].z;
					}
					dpos++;
				}
			}
		}
	}
	else {
		if (alpha != 255) {
			mat->color[3] = (double)alpha / (double)255;
		}
		for (f = 0; f < fnum; f++){
			if (F[f].m != matpos) continue;
			if (F[f].n == 3) {
				mqoSnormal(V[F[f].v[0]], V[F[f].v[1]], V[F[f].v[2]], &normal);		// �ｿｽ@�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽv�ｿｽZ
				for (i = 0; i < 3; i++) {
					mat->vertex_p[dpos].point[0] = V[F[f].v[i]].x*scale;
					mat->vertex_p[dpos].point[1] = V[F[f].v[i]].y*scale;
					mat->vertex_p[dpos].point[2] = V[F[f].v[i]].z*scale;
					mat->vertex_p[dpos].normal[0] = normal.x;
					mat->vertex_p[dpos].normal[1] = normal.y;
					mat->vertex_p[dpos].normal[2] = normal.z;
					s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
					if (facet < s) {
						mat->vertex_p[dpos].normal[0] = normal.x;
						mat->vertex_p[dpos].normal[1] = normal.y;
						mat->vertex_p[dpos].normal[2] = normal.z;
					}
					else {
						mat->vertex_p[dpos].normal[0] = N[F[f].v[i]].x;
						mat->vertex_p[dpos].normal[1] = N[F[f].v[i]].y;
						mat->vertex_p[dpos].normal[2] = N[F[f].v[i]].z;
					}
					dpos++;
				}
			}
			//�ｿｽS�ｿｽ�ｿｽ�ｿｽ_�ｿｽi�ｿｽl�ｿｽp�ｿｽj�ｿｽﾍ３�ｿｽ�ｿｽ�ｿｽ_�ｿｽi�ｿｽO�ｿｽp�ｿｽj�ｿｽ�ｿｽ�ｿｽQ�ｿｽﾉ包ｿｽ�ｿｽ�ｿｽ
			if (F[f].n == 4) {
				mqoSnormal(V[F[f].v[0]], V[F[f].v[1]], V[F[f].v[2]], &normal);		// �ｿｽ@�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽv�ｿｽZ
				for (i = 0; i < 4; i++) {
					if (i == 3) continue;
					mat->vertex_p[dpos].point[0] = V[F[f].v[i]].x*scale;
					mat->vertex_p[dpos].point[1] = V[F[f].v[i]].y*scale;
					mat->vertex_p[dpos].point[2] = V[F[f].v[i]].z*scale;
					mat->vertex_p[dpos].normal[0] = normal.x;
					mat->vertex_p[dpos].normal[1] = normal.y;
					mat->vertex_p[dpos].normal[2] = normal.z;
					s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
					if (facet < s) {
						mat->vertex_p[dpos].normal[0] = normal.x;
						mat->vertex_p[dpos].normal[1] = normal.y;
						mat->vertex_p[dpos].normal[2] = normal.z;
					}
					else {
						mat->vertex_p[dpos].normal[0] = N[F[f].v[i]].x;
						mat->vertex_p[dpos].normal[1] = N[F[f].v[i]].y;
						mat->vertex_p[dpos].normal[2] = N[F[f].v[i]].z;
					}
					dpos++;
				}
				mqoSnormal(V[F[f].v[0]], V[F[f].v[2]], V[F[f].v[3]], &normal);		// �ｿｽ@�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽv�ｿｽZ
				for (i = 0; i < 4; i++) {
					if (i == 1) continue;
					mat->vertex_p[dpos].point[0] = V[F[f].v[i]].x*scale;
					mat->vertex_p[dpos].point[1] = V[F[f].v[i]].y*scale;
					mat->vertex_p[dpos].point[2] = V[F[f].v[i]].z*scale;
					mat->vertex_p[dpos].normal[0] = normal.x;
					mat->vertex_p[dpos].normal[1] = normal.y;
					mat->vertex_p[dpos].normal[2] = normal.z;
					s = acos(normal.x*N[F[f].v[i]].x + normal.y*N[F[f].v[i]].y + normal.z*N[F[f].v[i]].z);
					if (facet < s) {
						mat->vertex_p[dpos].normal[0] = normal.x;
						mat->vertex_p[dpos].normal[1] = normal.y;
						mat->vertex_p[dpos].normal[2] = normal.z;
					}
					else {
						mat->vertex_p[dpos].normal[0] = N[F[f].v[i]].x;
						mat->vertex_p[dpos].normal[1] = N[F[f].v[i]].y;
						mat->vertex_p[dpos].normal[2] = N[F[f].v[i]].z;
					}
					dpos++;
				}
			}
		}
	}
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoVertexNormal
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ�ｿｽ�ｿｽ_�ｿｽ@�ｿｽ�ｿｽ�ｿｽﾌ計�ｿｽZ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
obj			�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽ@�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽz�ｿｽS�ｿｽ�ｿｽ�ｿｽ_�ｿｽﾌ面は三�ｿｽp�ｿｽ`�ｿｽﾉ包ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄ計�ｿｽZ
�ｿｽﾟゑｿｽl�ｿｽﾍ必�ｿｽ�ｿｽ�ｿｽﾄび出�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾅ会ｿｽ�ｿｽ�ｿｽifree�ｿｽj�ｿｽ�ｿｽ�ｿｽ驍ｱ�ｿｽﾆ！
=========================================================================*/

glPOINT3f * mqoVertexNormal(MQO_OBJDATA *obj)
{
	int f;
	int v;
	int i;
	double len;
	glPOINT3f fnormal;	// �ｿｽﾊ法�ｿｽ�ｿｽ�ｿｽx�ｿｽN�ｿｽg�ｿｽ�ｿｽ
	MQO_FACE *F;
	glPOINT3f *V;
	glPOINT3f *ret;
	F = obj->F;
	V = obj->V;
	ret = (glPOINT3f *)calloc(obj->n_vertex, sizeof(glPOINT3f));
	//�ｿｽﾊの法�ｿｽ�ｿｽ�ｿｽｸ点�ｿｽﾉ托ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
	for (f = 0; f < obj->n_face; f++) {
		if (obj->F[f].n == 3) {
			mqoSnormal(V[F[f].v[0]], V[F[f].v[1]], V[F[f].v[2]], &fnormal);
			for (i = 0; i < 3; i++) {
				ret[F[f].v[i]].x += fnormal.x;
				ret[F[f].v[i]].y += fnormal.y;
				ret[F[f].v[i]].z += fnormal.z;
			}
		}
		if (obj->F[f].n == 4) {
			mqoSnormal(V[F[f].v[0]], V[F[f].v[1]], V[F[f].v[2]], &fnormal);
			for (i = 0; i < 4; i++) {
				if (i == 3) continue;
				ret[F[f].v[i]].x += fnormal.x;
				ret[F[f].v[i]].y += fnormal.y;
				ret[F[f].v[i]].z += fnormal.z;
			}
			mqoSnormal(V[F[f].v[0]], V[F[f].v[2]], V[F[f].v[3]], &fnormal);
			for (i = 0; i < 4; i++) {
				if (i == 1) continue;
				ret[F[f].v[i]].x += fnormal.x;
				ret[F[f].v[i]].y += fnormal.y;
				ret[F[f].v[i]].z += fnormal.z;
			}
		}
	}
	//�ｿｽ�ｿｽ�ｿｽK�ｿｽ�ｿｽ
	for (v = 0; v < obj->n_vertex; v++) {
		if (ret[v].x == 0 && ret[v].y == 0 && ret[v].z == 0) {
			//�ｿｽﾊに使�ｿｽ�ｿｽ�ｿｽﾄなゑｿｽ�ｿｽ_
			continue;
		}
		len = sqrt(ret[v].x*ret[v].x + ret[v].y*ret[v].y + ret[v].z*ret[v].z);
		if (len != 0) {
			ret[v].x = ret[v].x / len;
			ret[v].y = ret[v].y / len;
			ret[v].z = ret[v].z / len;
		}
	}

	return ret;
}

/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoMakePolygon
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽ|�ｿｽ�ｿｽ�ｿｽS�ｿｽ�ｿｽ�ｿｽﾌ撰ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
readObj		�ｿｽﾇみ搾ｿｽ�ｿｽｾオ�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ
mqoobj		MQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg
N[]			�ｿｽ@�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ
M[]			�ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ
n_mat		�ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ
scale		�ｿｽX�ｿｽP�ｿｽ[�ｿｽ�ｿｽ
alpha		�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void mqoMakePolygon(MQO_OBJDATA *readObj, MQO_OBJECT *mqoobj,
	glPOINT3f N[], MQO_MATDATA M[], int n_mat, double scale, unsigned char alpha)
{

	MQO_INNER_OBJECT		*setObj;
	MQO_MATERIAL			*material;
	glCOLOR4f				defcol;
	glCOLOR4f				*pcol;
	int						f, m, *mat_vnum;
	int						fnum;
	MQO_FACE				*F;
	glPOINT3f				*V;
	double					facet;


	setObj = &mqoobj->obj[mqoobj->objnum];
	strcpy(setObj->objname, readObj->objname);
	setObj->isVisible = readObj->visible;
	setObj->isShadingFlat = (readObj->shading == 0);
	F = readObj->F;
	fnum = readObj->n_face;
	V = readObj->V;
	facet = readObj->facet;

	// face�ｿｽﾌ抵ｿｽ�ｿｽﾅのマ�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌ抵ｿｽ�ｿｽ_�ｿｽﾌ撰ｿｽ
	// M=NULL�ｿｽﾌとゑｿｽ�ｿｽAF[].m = 0 �ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ�ｿｽ
	if (M == NULL) n_mat = 1;

	mat_vnum = (int *)malloc(sizeof(int)*n_mat);
	memset(mat_vnum, 0, sizeof(int)*n_mat);

	for (f = 0; f < fnum; f++){
		if (F[f].m < 0) continue; // �ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾝ定さ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽﾈゑｿｽ�ｿｽ�ｿｽ
		if (F[f].n == 3) {
			mat_vnum[F[f].m] += 3;
		}
		if (F[f].n == 4) {
			//�ｿｽS�ｿｽ�ｿｽ�ｿｽ_�ｿｽi�ｿｽl�ｿｽp�ｿｽj�ｿｽﾍ３�ｿｽ�ｿｽ�ｿｽ_�ｿｽi�ｿｽO�ｿｽp�ｿｽj�ｿｽ�ｿｽ�ｿｽQ�ｿｽﾉ包ｿｽ�ｿｽ�ｿｽ
			//  0  3      0    0  3
			//   �ｿｽ�ｿｽ   �ｿｽ�ｿｽ�ｿｽ@�ｿｽ�ｿｽ�ｿｽ@�ｿｽ@�ｿｽ�ｿｽ
			//  1  2     1  2   2
			// �ｿｽS�ｿｽ�ｿｽ�ｿｽ_�ｿｽﾌ包ｿｽ�ｿｽﾊデ�ｿｽ[�ｿｽ^�ｿｽ�ｿｽ
			// �ｿｽR�ｿｽ�ｿｽ�ｿｽ_�ｿｽﾌ包ｿｽ�ｿｽﾊデ�ｿｽ[�ｿｽ^�ｿｽ�ｿｽ�ｿｽQ�ｿｽ�ｿｽ
			mat_vnum[F[f].m] += 3 * 2;
		}
		if (setObj->matnum < F[f].m + 1) setObj->matnum = F[f].m + 1;
	}

	// �ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽﾊに抵ｿｽ�ｿｽ_�ｿｽz�ｿｽ�ｿｽ�ｿｽ�ｿｽ�成�ｿｽ�ｿｽ�ｿｽ�ｿｽ
	setObj->mat = (MQO_MATERIAL *)malloc(sizeof(MQO_MATERIAL)*setObj->matnum);
	memset(setObj->mat, 0, sizeof(MQO_MATERIAL)*setObj->matnum);

	for (m = 0; m < setObj->matnum; m++) {
		material = &setObj->mat[m];
		material->datanum = mat_vnum[m];
		material->isValidMaterialInfo = (M != NULL);

		if (mat_vnum[m] <= 0) continue;
		if (material->isValidMaterialInfo) {
			memcpy(material->dif, M[m].dif, sizeof(material->dif));
			memcpy(material->amb, M[m].amb, sizeof(material->amb));
			memcpy(material->spc, M[m].spc, sizeof(material->spc));
			memcpy(material->emi, M[m].emi, sizeof(material->emi));
			material->power = M[m].power;
			material->isUseTexture = M[m].useTex;
			pcol = &M[m].col;
		}
		else {
			defcol.r = 1.0;
			defcol.g = 1.0;
			defcol.b = 1.0;
			defcol.a = 1.0;
			material->isUseTexture = 0;
			pcol = &defcol;
		}
		if (material->isUseTexture) {
			material->vertex_t = (VERTEX_TEXUSE *)calloc(material->datanum, sizeof(VERTEX_TEXUSE));
			material->texture_id = M[m].texName;
		}
		else {
			material->vertex_p = (VERTEX_NOTEX *)calloc(material->datanum, sizeof(VERTEX_NOTEX));
		}
		mqoMakeArray(material, m, F, fnum, V, N, facet, pcol, scale, alpha);
		if (g_isVBOSupported) {
			if (material->isUseTexture) {
				glGenBuffersARB(1, &material->VBO_id);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, material->VBO_id);
				glBufferDataARB(GL_ARRAY_BUFFER_ARB, material->datanum*sizeof(VERTEX_TEXUSE), material->vertex_t, GL_STATIC_DRAW_ARB);
			}
			else {
				glGenBuffersARB(1, &material->VBO_id);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, material->VBO_id);
				glBufferDataARB(GL_ARRAY_BUFFER_ARB, material->datanum*sizeof(VERTEX_NOTEX), material->vertex_p, GL_STATIC_DRAW_ARB);
			}
		}
	}
	mqoobj->objnum++;
	if (MAX_OBJECT <= mqoobj->objnum) {
		printf("MQO�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽﾇみ搾ｿｽ�ｿｽﾝ：�ｿｽ@�ｿｽﾅ托ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽｴゑｿｽ�ｿｽﾜゑｿｽ�ｿｽ�ｿｽ[%d]\n", mqoobj->objnum);
		mqoobj->objnum = MAX_OBJECT - 1;
	}

	free(mat_vnum);

}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoMakeObjectsEx
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽﾌデ�ｿｽ[�ｿｽ^�ｿｽ�ｿｽ�ｿｽ�ｿｽ|�ｿｽ�ｿｽ�ｿｽS�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽf�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�成�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
mqoobj	MQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg
obj		�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽz�ｿｽ�ｿｽ
n_obj	�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽﾌ個撰ｿｽ
M		�ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽz�ｿｽ�ｿｽ
n_mat	�ｿｽ}�ｿｽe�ｿｽ�ｿｽ�ｿｽA�ｿｽ�ｿｽ�ｿｽﾌ個撰ｿｽ
scale	�ｿｽg�ｿｽ蝸ｦ
alpha	�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void mqoMakeObjectsEx(MQO_OBJECT *mqoobj, MQO_OBJDATA obj[], int n_obj, MQO_MATDATA M[], int n_mat,
	double scale, unsigned char alpha)
{
	int i;
	glPOINT3f *N;
	for (i = 0; i<n_obj; i++) {
		N = mqoVertexNormal(&obj[i]);
		mqoMakePolygon(
			&obj[i],
			mqoobj,
			N,
			M, n_mat,
			scale,
			alpha);
		free(N);
	}
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoCreateModel
�ｿｽy�ｿｽp�ｿｽr�ｿｽzMQO�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽMQO�ｿｽ�ｿｽ�ｿｽf�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�成�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
filename	MQO�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ
scale		�ｿｽg�ｿｽ蝸ｦ�ｿｽi1.0�ｿｽﾅゑｿｽ�ｿｽﾌまま）

�ｿｽy�ｿｽﾟ値�ｿｽzMQO_MODEL�ｿｽiMQO�ｿｽ�ｿｽ�ｿｽf�ｿｽ�ｿｽ�ｿｽj
=========================================================================*/

MQO_MODEL mqoCreateModel(char *filename, double scale)
{
	MQO_MODEL ret;
	ret = mqoCreateList(1);
	if (mqoCreateListObject(ret, 1 - 1, filename, scale, (unsigned char)255) < 0) {
		mqoDeleteObject(ret, 1);
		ret = NULL;
	}
	return ret;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoCreateSequenceEx
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽA�ｿｽﾔゑｿｽMQO�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽMQO�ｿｽV�ｿｽ[�ｿｽP�ｿｽ�ｿｽ�ｿｽX�ｿｽ�ｿｽ�ｿｽ�成�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
format		�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌ擾ｿｽ�ｿｽ�ｿｽ
n_file		�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ
scale		�ｿｽg�ｿｽ蝸ｦ�ｿｽi1.0�ｿｽﾅゑｿｽ�ｿｽﾌまま）
fade_inout	0:�ｿｽ�ｿｽ�ｿｽﾌまま　�ｿｽ�ｿｽ�ｿｽF�ｿｽt�ｿｽF�ｿｽ[�ｿｽh�ｿｽC�ｿｽ�ｿｽ�ｿｽ@�ｿｽ�ｿｽ�ｿｽF�ｿｽt�ｿｽF�ｿｽ[�ｿｽh�ｿｽA�ｿｽE�ｿｽg
�ｿｽ�ｿｽﾎ値�ｿｽﾍ鯉ｿｽ�ｿｽﾊゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽt�ｿｽ�ｿｽ�ｿｽ[�ｿｽ�ｿｽ�ｿｽ�ｿｽ
alpha		�ｿｽA�ｿｽ�ｿｽ�ｿｽt�ｿｽ@

�ｿｽy�ｿｽﾟ値�ｿｽzMQO_SEQUENCE�ｿｽiMQO�ｿｽV�ｿｽ[�ｿｽP�ｿｽ�ｿｽ�ｿｽX�ｿｽj
�ｿｽy�ｿｽ�ｿｽ�ｿｽl�ｿｽz�ｿｽA�ｿｽﾔゑｿｽ0�ｿｽ�ｿｽ�ｿｽ�ｿｽJ�ｿｽn
=========================================================================*/

MQO_SEQUENCE mqoCreateSequenceEx(const char *format, int n_file, double scale,
	int fade_inout, unsigned char alpha)
{
	MQO_SEQUENCE retSeq;
	int iret;
	int seq;
	char filename[SIZE_STR];
	short setAlpha;
	short calAlpha;
	int frames;

	retSeq.n_frame = 0;
	if (format == NULL) {
		return retSeq;
	}
	calAlpha = alpha;
	frames = abs(fade_inout);
	frames = MAX(frames, n_file);
	setAlpha = (fade_inout <= 0) ? alpha : 0;

	retSeq.model = mqoCreateList(n_file);
	for (seq = 0; seq < frames; seq++) {
		if (seq < n_file) {
			sprintf(filename, format, seq);
		}
		if ((fade_inout != 0) && ((frames - 1) == seq)) {
			setAlpha = (fade_inout<0) ? 0 : calAlpha;
		}
		iret = mqoCreateListObject(retSeq.model, seq, filename, scale, (unsigned char)setAlpha);
		if (iret == -1) {
			seq--;
			mqoClearObject(retSeq.model, seq, n_file - seq);
			break;
		}
		if (fade_inout != 0) {
			if (fade_inout<0) {
				if ((n_file - seq) <= (-1 * fade_inout)) {
					setAlpha -= (calAlpha / (-1 * fade_inout));
					if (setAlpha < 0) setAlpha = 0;
				}
			}
			else {
				setAlpha += (calAlpha / fade_inout);
				if (calAlpha < setAlpha) setAlpha = calAlpha;
			}
		}
	}
	retSeq.n_frame = seq;
	return retSeq;
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoCreateSequence
�ｿｽy�ｿｽp�ｿｽr�ｿｽz�ｿｽA�ｿｽﾔゑｿｽMQO�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽMQO�ｿｽV�ｿｽ[�ｿｽP�ｿｽ�ｿｽ�ｿｽX�ｿｽ�ｿｽ�ｿｽ�成�ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
format		�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾌフ�ｿｽH�ｿｽ[�ｿｽ}�ｿｽb�ｿｽg
n_file		�ｿｽt�ｿｽ@�ｿｽC�ｿｽ�ｿｽ�ｿｽ�ｿｽ
scale		�ｿｽg�ｿｽ蝸ｦ�ｿｽi1.0�ｿｽﾅゑｿｽ�ｿｽﾌまま）

�ｿｽy�ｿｽﾟ値�ｿｽzMQO_SEQUENCE�ｿｽiMQO�ｿｽV�ｿｽ[�ｿｽP�ｿｽ�ｿｽ�ｿｽX�ｿｽj
�ｿｽy�ｿｽ�ｿｽ�ｿｽl�ｿｽz�ｿｽA�ｿｽﾔゑｿｽ0�ｿｽ�ｿｽ�ｿｽ�ｿｽJ�ｿｽn
=========================================================================*/

MQO_SEQUENCE mqoCreateSequence(const char *format, int n_file, double scale)
{
	return mqoCreateSequenceEx(format, n_file, scale, 0, (unsigned char)255);
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoCallModel
�ｿｽy�ｿｽp�ｿｽr�ｿｽzMQO�ｿｽ�ｿｽ�ｿｽf�ｿｽ�ｿｽ�ｿｽ�ｿｽOpenGL�ｿｽﾌ会ｿｽﾊ擾ｿｽﾉ呼び出�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
model		MQO�ｿｽ�ｿｽ�ｿｽf�ｿｽ�ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void mqoCallModel(MQO_MODEL model)
{
	mqoCallListObject(model, 0);
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoCallSequence
�ｿｽy�ｿｽp�ｿｽr�ｿｽzMQO�ｿｽV�ｿｽ[�ｿｽP�ｿｽ�ｿｽ�ｿｽX�ｿｽ�ｿｽOpenGL�ｿｽﾌ会ｿｽﾊに呼び出�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
seq		MQO�ｿｽV�ｿｽ[�ｿｽP�ｿｽ�ｿｽ�ｿｽX
i		�ｿｽt�ｿｽ�ｿｽ�ｿｽ[�ｿｽ�ｿｽ�ｿｽﾔ搾ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽd�ｿｽl�ｿｽzMQO�ｿｽV�ｿｽ[�ｿｽP�ｿｽ�ｿｽ�ｿｽX�ｿｽﾌ抵ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽw�ｿｽ閧ｵ�ｿｽ�ｿｽ�ｿｽt�ｿｽ�ｿｽ�ｿｽ[�ｿｽ�ｿｽ�ｿｽﾔ搾ｿｽ�ｿｽﾌ��ｿｽ�ｿｽf�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄび出�ｿｽ�ｿｽ
=========================================================================*/

void mqoCallSequence(MQO_SEQUENCE seq, int i)
{
	if (i >= 0 && i<seq.n_frame) {
		mqoCallListObject(seq.model, i);
	}
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoClearObject
�ｿｽy�ｿｽp�ｿｽr�ｿｽzMQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽﾌク�ｿｽ�ｿｽ�ｿｽA
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
object	MQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽz�ｿｽ�ｿｽ
from	�ｿｽ尞懶ｿｽJ�ｿｽn�ｿｽﾔ搾ｿｽ�ｿｽi0�ｿｽ`�ｿｽj
num		�ｿｽ尞懶ｿｽ�ｿｽ�ｿｽ�ｿｽﾂ撰ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void mqoClearObject(MQO_OBJECT object[], int from, int num)
{
	int					loop, o, m;
	MQO_INNER_OBJECT	*obj;
	MQO_MATERIAL		*mat;

	if (object == NULL) return;

	for (loop = from; loop < from + num; loop++) {
		for (o = 0; o < (object + from)->objnum; o++) {

			obj = &(object + loop)->obj[o];
			for (m = 0; m < obj->matnum; m++) {
				mat = &obj->mat[m];
				if (mat->datanum <= 0) continue;
				if (g_isVBOSupported) {
					// �ｿｽ�ｿｽ�ｿｽ_�ｿｽo�ｿｽb�ｿｽt�ｿｽ@�ｿｽﾌ削除
					glDeleteBuffersARB(1, &mat->VBO_id);
				}

				// �ｿｽ�ｿｽ�ｿｽ_�ｿｽz�ｿｽ�ｿｽﾌ削除
				if (mat->isUseTexture) {
					if (mat->vertex_t != NULL) {
						free(mat->vertex_t);
						mat->vertex_t = NULL;
					}
				}
				else {
					if (mat->vertex_p != NULL) {
						free(mat->vertex_p);
						mat->vertex_p = NULL;
					}
				}
			}
			if (obj->mat != NULL) {
				free(obj->mat);
				obj->mat = NULL;
			}
			obj->matnum = 0;
		}
	}

}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoDeleteObject
�ｿｽy�ｿｽp�ｿｽr�ｿｽzMQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽ�ｿｽ�ｿｽ尞懶ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
object	MQO�ｿｽI�ｿｽu�ｿｽW�ｿｽF�ｿｽN�ｿｽg�ｿｽz�ｿｽ�ｿｽ
num		�ｿｽ尞懶ｿｽ�ｿｽ�ｿｽ�ｿｽﾂ撰ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
=========================================================================*/

void mqoDeleteObject(MQO_OBJECT object[], int num)
{
	mqoClearObject(object, 0, num);
	free(object);
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoDeleteModel
�ｿｽy�ｿｽp�ｿｽr�ｿｽzMQO�ｿｽ�ｿｽ�ｿｽf�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ尞懶ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
model	MQO�ｿｽ�ｿｽ�ｿｽf�ｿｽ�ｿｽ

�ｿｽy�ｿｽﾟ値�ｿｽz�ｿｽﾈゑｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽl�ｿｽz�ｿｽ尞懶ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽs�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾏ撰ｿｽ�ｿｽ�ｿｽ�ｿｽﾄ暦ｿｽ�ｿｽp�ｿｽ�ｿｽ�ｿｽ�ｿｽﾂ能�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ鼾��ｿｽ�ｿｽ
�ｿｽ�ｿｽ�ｿｽﾌ関撰ｿｽ�ｿｽﾌ趣ｿｽ�ｿｽs�ｿｽ�ｿｽ�ｿｽNULL�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
=========================================================================*/

void mqoDeleteModel(MQO_MODEL model)
{
	mqoDeleteObject(model, 1);
}


/*=========================================================================
�ｿｽy�ｿｽﾖ撰ｿｽ�ｿｽzmqoDeleteSequence
�ｿｽy�ｿｽp�ｿｽr�ｿｽzMQO�ｿｽV�ｿｽ[�ｿｽP�ｿｽ�ｿｽ�ｿｽX�ｿｽ�ｿｽ�ｿｽ尞懶ｿｽ�ｿｽ�ｿｽ�ｿｽ
�ｿｽy�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽz
seq		MQO�ｿｽV�ｿｽ[�ｿｽP�ｿｽ�ｿｽ�ｿｽX

�ｿｽy�ｿｽ�ｿｽ�ｿｽl�ｿｽz�ｿｽ尞懶ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽs�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾏ撰ｿｽ�ｿｽ�ｿｽ�ｿｽﾄ暦ｿｽ�ｿｽp�ｿｽ�ｿｽ�ｿｽ�ｿｽﾂ能�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ鼾��ｿｽ�ｿｽ
�ｿｽ�ｿｽ�ｿｽﾌ関撰ｿｽ�ｿｽﾌ趣ｿｽ�ｿｽs�ｿｽ�ｿｽ�ｿｽNULL�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽﾄゑｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ�ｿｽ
=========================================================================*/

void mqoDeleteSequence(MQO_SEQUENCE seq)
{
	mqoDeleteObject(seq.model, seq.n_frame);
}
