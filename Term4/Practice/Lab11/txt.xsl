<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="text"/>
<xsl:template match="/">
=============
| Book list |
=============
<xsl:for-each select="books/book">
<xsl:value-of select="concat('• ', title, ' by ', author, ', ', pages, ' pages. ISBN: ', @isbn, ', Year: ', @year, '.&#13;')"/>
</xsl:for-each>


<xsl:value-of select="concat('&#13;', 'Count of pages: ', sum(books/book/pages), '&#13;')"/>
<xsl:value-of select="concat('Average page count: ', sum(books/book/pages) div count(books/book), '&#13;')"/>

</xsl:template>
</xsl:stylesheet>
