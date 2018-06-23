<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:variable name="apos">'</xsl:variable>

    <xsl:output method="html"/>

    <xsl:template match="/">
        <html>
			<head>
			<style>
				table {
					color:#666;
					width: 95%;
					font-size:16px;
					text-shadow: 1px 1px 0px #fff;
					background:#eaebec;
					margin:20px;
					border:#ccc 1px solid;
					border-radius:3px;
					box-shadow: 0 1px 2px #d1d1d1;
				}
				table th {
					padding:21px 25px 22px 25px;
					border-top:1px solid #fafafa;
					border-bottom:1px solid #e0e0e0;
					background: #ededed;
				}
				table tr {
					text-align: center;
					padding-left:20px;
				}


				table td {
					padding:18px;
					border-top: 1px solid #ffffff;
					border-bottom:1px solid #e0e0e0;
					border-left: 1px solid #e0e0e0;
				}
				tr:nth-child(even) {
					background-color: #CCC 
				}
				tr:nth-child(odd) {
					background-color: #FFF 
				}
			</style>
			</head>
            <body>
                <table>
                    <tr>
					    <td align="center"><strong>Cover</strong></td>
                        <td align="center"><strong>Title</strong></td>
                        <td align="center"><strong>Author</strong></td>
                        <td align="center"><strong>ISBN</strong></td>
                        <td align="center"><strong>Year</strong></td>
                        <td align="center"><strong>Pages</strong></td>
                    </tr>

                    <xsl:for-each select="books/book">
                        <tr>
							<td><img>
								<xsl:attribute name="src">http://covers.librarything.com/devkey/f6feb0bbb99e3578e21a592170d90571/medium/isbn/<xsl:value-of select="@isbn"/></xsl:attribute>
							</img></td>
                            <td><xsl:value-of select="title"/></td>
                            <td><xsl:value-of select="author"/></td>
                            <td><xsl:value-of select="@isbn"/></td>
                            <td><xsl:value-of select="@year"/></td>
                            <td><xsl:value-of select="pages"/></td>
                        </tr>
                    </xsl:for-each>

                    <tr>
						<td></td><td></td><td></td>
                        <td><strong>Count of pages: </strong></td>
                        <td><xsl:value-of select="sum(books/book/pages)"/></td>
                    </tr>
					<tr>
						<td></td><td></td><td></td>
                        <td><strong>Average page count:</strong></td>
                        <td><xsl:value-of select="sum(books/book/pages) div count(books/book)"/></td>
                    </tr>
                </table>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>