<html>
	<head>
		<meta charset="UTF-8" />
		<title>ItemIDVector</title>

		<style>
			pre {
				-o-tab-size: 4;
				-moz-tab-size: 4;
				tab-size: 4;
			}
		</style>

	</head>
	<body>
		<pre><code>
class CItemIDVector : protected std::vector< UCHAR >
{
public:
	CItemIDVector() { }

	CItemIDVector( ITEMIDLIST *idl )
	{
		int sz = CalcSize( idl );
		resize( sz );
		memcpy( data(), idl, sz );
	}

	static int CalcSize( ITEMIDLIST *idl )
	{
		int sz = 2;
		ITEMIDLIST *p = idl;
		while( p->mkid.cb )
		{
			sz += p->mkid.cb;
			p = (ITEMIDLIST *)( (char*)p + p->mkid.cb );
		}
		return sz;
	}
};


void
unit_test()
{
	LPITEMIDLIST pidl;

	std::map< CItemIDVector, int > mapIDLtoID;

	pidl = ::SHSimpleIDListFromPath( LR"(C:\src\testprj)" );
	mapIDLtoID[ pidl ] = 1;
	::ILFree( pidl );

	pidl = ::SHSimpleIDListFromPath( LR"(D:\work)" );
	mapIDLtoID[ pidl ] = 2;
	::ILFree( pidl );

	pidl = ::SHSimpleIDListFromPath( LR"(C:\work)" );
	mapIDLtoID[ pidl ] = 3;
	::ILFree( pidl );



	pidl = ::SHSimpleIDListFromPath( LR"(D:\work)" );
	int n = mapIDLtoID[ pidl ];
	::ILFree( pidl );
}
		</code></pre>
	</body>
</html>

