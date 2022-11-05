// Generated from /Users/joshuatapp/Documents/UVA/CS4620/sipc-tapp/tipg4/TIP.g4 by ANTLR 4.9.2
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class TIPLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.9.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, MUL=17, 
		DIV=18, ADD=19, SUB=20, GT=21, LT=22, GTE=23, LTE=24, EQ=25, NE=26, MOD=27, 
		LNOT=28, LAND=29, LOR=30, DEC=31, INC=32, LEN=33, BOOLEAN=34, NUMBER=35, 
		INEQUALITY_OP=36, EQUALITY_OP=37, MULTIPLICATIVE_OP=38, ADDITIVE_OP=39, 
		POSTFIX_OP=40, KALLOC=41, KINPUT=42, KWHILE=43, KIF=44, KFOR=45, KELSE=46, 
		KVAR=47, KRETURN=48, KNULL=49, KOUTPUT=50, KERROR=51, KTRUE=52, KFALSE=53, 
		KNOT=54, KAND=55, KOR=56, IDENTIFIER=57, WS=58, BLOCKCOMMENT=59, COMMENT=60;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "MUL", 
			"DIV", "ADD", "SUB", "GT", "LT", "GTE", "LTE", "EQ", "NE", "MOD", "LNOT", 
			"LAND", "LOR", "DEC", "INC", "LEN", "BOOLEAN", "NUMBER", "INEQUALITY_OP", 
			"EQUALITY_OP", "MULTIPLICATIVE_OP", "ADDITIVE_OP", "POSTFIX_OP", "KALLOC", 
			"KINPUT", "KWHILE", "KIF", "KFOR", "KELSE", "KVAR", "KRETURN", "KNULL", 
			"KOUTPUT", "KERROR", "KTRUE", "KFALSE", "KNOT", "KAND", "KOR", "IDENTIFIER", 
			"WS", "BLOCKCOMMENT", "COMMENT"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "','", "')'", "'{'", "'}'", "';'", "'.'", "'['", "']'", 
			"'&'", "'?'", "':'", "'of'", "'..'", "'by'", "'='", "'*'", "'/'", "'+'", 
			"'-'", "'>'", "'<'", "'>='", "'<='", "'=='", "'!='", "'%'", null, null, 
			null, "'--'", "'++'", "'#'", null, null, null, null, null, null, null, 
			"'alloc'", "'input'", "'while'", "'if'", "'for'", "'else'", "'var'", 
			"'return'", "'null'", "'output'", "'error'", "'true'", "'false'", "'not'", 
			"'and'", "'or'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, "MUL", "DIV", "ADD", "SUB", "GT", "LT", 
			"GTE", "LTE", "EQ", "NE", "MOD", "LNOT", "LAND", "LOR", "DEC", "INC", 
			"LEN", "BOOLEAN", "NUMBER", "INEQUALITY_OP", "EQUALITY_OP", "MULTIPLICATIVE_OP", 
			"ADDITIVE_OP", "POSTFIX_OP", "KALLOC", "KINPUT", "KWHILE", "KIF", "KFOR", 
			"KELSE", "KVAR", "KRETURN", "KNULL", "KOUTPUT", "KERROR", "KTRUE", "KFALSE", 
			"KNOT", "KAND", "KOR", "IDENTIFIER", "WS", "BLOCKCOMMENT", "COMMENT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public TIPLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "TIP.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2>\u015e\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\4:\t:\4;\t;\4<\t<\4=\t="+
		"\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3"+
		"\n\3\13\3\13\3\f\3\f\3\r\3\r\3\16\3\16\3\16\3\17\3\17\3\17\3\20\3\20\3"+
		"\20\3\21\3\21\3\22\3\22\3\23\3\23\3\24\3\24\3\25\3\25\3\26\3\26\3\27\3"+
		"\27\3\30\3\30\3\30\3\31\3\31\3\31\3\32\3\32\3\32\3\33\3\33\3\33\3\34\3"+
		"\34\3\35\3\35\3\36\3\36\3\37\3\37\3 \3 \3 \3!\3!\3!\3\"\3\"\3#\3#\5#\u00c9"+
		"\n#\3$\6$\u00cc\n$\r$\16$\u00cd\3%\3%\3%\3%\5%\u00d4\n%\3&\3&\5&\u00d8"+
		"\n&\3\'\3\'\3\'\5\'\u00dd\n\'\3(\3(\5(\u00e1\n(\3)\3)\5)\u00e5\n)\3*\3"+
		"*\3*\3*\3*\3*\3+\3+\3+\3+\3+\3+\3,\3,\3,\3,\3,\3,\3-\3-\3-\3.\3.\3.\3"+
		".\3/\3/\3/\3/\3/\3\60\3\60\3\60\3\60\3\61\3\61\3\61\3\61\3\61\3\61\3\61"+
		"\3\62\3\62\3\62\3\62\3\62\3\63\3\63\3\63\3\63\3\63\3\63\3\63\3\64\3\64"+
		"\3\64\3\64\3\64\3\64\3\65\3\65\3\65\3\65\3\65\3\66\3\66\3\66\3\66\3\66"+
		"\3\66\3\67\3\67\3\67\3\67\38\38\38\38\39\39\39\3:\3:\7:\u013a\n:\f:\16"+
		":\u013d\13:\3;\6;\u0140\n;\r;\16;\u0141\3;\3;\3<\3<\3<\3<\7<\u014a\n<"+
		"\f<\16<\u014d\13<\3<\3<\3<\3<\3<\3=\3=\3=\3=\7=\u0158\n=\f=\16=\u015b"+
		"\13=\3=\3=\3\u014b\2>\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27"+
		"\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33"+
		"\65\34\67\359\36;\37= ?!A\"C#E$G%I&K\'M(O)Q*S+U,W-Y.[/]\60_\61a\62c\63"+
		"e\64g\65i\66k\67m8o9q:s;u<w=y>\3\2\7\3\2\62;\5\2C\\aac|\6\2\62;C\\aac"+
		"|\5\2\13\f\17\17\"\"\4\2\f\f\17\17\2\u016b\2\3\3\2\2\2\2\5\3\2\2\2\2\7"+
		"\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2"+
		"\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2"+
		"\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2"+
		"\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61\3\2\2\2\2\63\3\2\2\2"+
		"\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2\2=\3\2\2\2\2?\3\2\2\2"+
		"\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I\3\2\2\2\2K\3\2\2\2\2M"+
		"\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2S\3\2\2\2\2U\3\2\2\2\2W\3\2\2\2\2Y\3\2"+
		"\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3\2\2\2\2a\3\2\2\2\2c\3\2\2\2\2e\3\2\2\2"+
		"\2g\3\2\2\2\2i\3\2\2\2\2k\3\2\2\2\2m\3\2\2\2\2o\3\2\2\2\2q\3\2\2\2\2s"+
		"\3\2\2\2\2u\3\2\2\2\2w\3\2\2\2\2y\3\2\2\2\3{\3\2\2\2\5}\3\2\2\2\7\177"+
		"\3\2\2\2\t\u0081\3\2\2\2\13\u0083\3\2\2\2\r\u0085\3\2\2\2\17\u0087\3\2"+
		"\2\2\21\u0089\3\2\2\2\23\u008b\3\2\2\2\25\u008d\3\2\2\2\27\u008f\3\2\2"+
		"\2\31\u0091\3\2\2\2\33\u0093\3\2\2\2\35\u0096\3\2\2\2\37\u0099\3\2\2\2"+
		"!\u009c\3\2\2\2#\u009e\3\2\2\2%\u00a0\3\2\2\2\'\u00a2\3\2\2\2)\u00a4\3"+
		"\2\2\2+\u00a6\3\2\2\2-\u00a8\3\2\2\2/\u00aa\3\2\2\2\61\u00ad\3\2\2\2\63"+
		"\u00b0\3\2\2\2\65\u00b3\3\2\2\2\67\u00b6\3\2\2\29\u00b8\3\2\2\2;\u00ba"+
		"\3\2\2\2=\u00bc\3\2\2\2?\u00be\3\2\2\2A\u00c1\3\2\2\2C\u00c4\3\2\2\2E"+
		"\u00c8\3\2\2\2G\u00cb\3\2\2\2I\u00d3\3\2\2\2K\u00d7\3\2\2\2M\u00dc\3\2"+
		"\2\2O\u00e0\3\2\2\2Q\u00e4\3\2\2\2S\u00e6\3\2\2\2U\u00ec\3\2\2\2W\u00f2"+
		"\3\2\2\2Y\u00f8\3\2\2\2[\u00fb\3\2\2\2]\u00ff\3\2\2\2_\u0104\3\2\2\2a"+
		"\u0108\3\2\2\2c\u010f\3\2\2\2e\u0114\3\2\2\2g\u011b\3\2\2\2i\u0121\3\2"+
		"\2\2k\u0126\3\2\2\2m\u012c\3\2\2\2o\u0130\3\2\2\2q\u0134\3\2\2\2s\u0137"+
		"\3\2\2\2u\u013f\3\2\2\2w\u0145\3\2\2\2y\u0153\3\2\2\2{|\7*\2\2|\4\3\2"+
		"\2\2}~\7.\2\2~\6\3\2\2\2\177\u0080\7+\2\2\u0080\b\3\2\2\2\u0081\u0082"+
		"\7}\2\2\u0082\n\3\2\2\2\u0083\u0084\7\177\2\2\u0084\f\3\2\2\2\u0085\u0086"+
		"\7=\2\2\u0086\16\3\2\2\2\u0087\u0088\7\60\2\2\u0088\20\3\2\2\2\u0089\u008a"+
		"\7]\2\2\u008a\22\3\2\2\2\u008b\u008c\7_\2\2\u008c\24\3\2\2\2\u008d\u008e"+
		"\7(\2\2\u008e\26\3\2\2\2\u008f\u0090\7A\2\2\u0090\30\3\2\2\2\u0091\u0092"+
		"\7<\2\2\u0092\32\3\2\2\2\u0093\u0094\7q\2\2\u0094\u0095\7h\2\2\u0095\34"+
		"\3\2\2\2\u0096\u0097\7\60\2\2\u0097\u0098\7\60\2\2\u0098\36\3\2\2\2\u0099"+
		"\u009a\7d\2\2\u009a\u009b\7{\2\2\u009b \3\2\2\2\u009c\u009d\7?\2\2\u009d"+
		"\"\3\2\2\2\u009e\u009f\7,\2\2\u009f$\3\2\2\2\u00a0\u00a1\7\61\2\2\u00a1"+
		"&\3\2\2\2\u00a2\u00a3\7-\2\2\u00a3(\3\2\2\2\u00a4\u00a5\7/\2\2\u00a5*"+
		"\3\2\2\2\u00a6\u00a7\7@\2\2\u00a7,\3\2\2\2\u00a8\u00a9\7>\2\2\u00a9.\3"+
		"\2\2\2\u00aa\u00ab\7@\2\2\u00ab\u00ac\7?\2\2\u00ac\60\3\2\2\2\u00ad\u00ae"+
		"\7>\2\2\u00ae\u00af\7?\2\2\u00af\62\3\2\2\2\u00b0\u00b1\7?\2\2\u00b1\u00b2"+
		"\7?\2\2\u00b2\64\3\2\2\2\u00b3\u00b4\7#\2\2\u00b4\u00b5\7?\2\2\u00b5\66"+
		"\3\2\2\2\u00b6\u00b7\7\'\2\2\u00b78\3\2\2\2\u00b8\u00b9\5m\67\2\u00b9"+
		":\3\2\2\2\u00ba\u00bb\5o8\2\u00bb<\3\2\2\2\u00bc\u00bd\5q9\2\u00bd>\3"+
		"\2\2\2\u00be\u00bf\7/\2\2\u00bf\u00c0\7/\2\2\u00c0@\3\2\2\2\u00c1\u00c2"+
		"\7-\2\2\u00c2\u00c3\7-\2\2\u00c3B\3\2\2\2\u00c4\u00c5\7%\2\2\u00c5D\3"+
		"\2\2\2\u00c6\u00c9\5i\65\2\u00c7\u00c9\5k\66\2\u00c8\u00c6\3\2\2\2\u00c8"+
		"\u00c7\3\2\2\2\u00c9F\3\2\2\2\u00ca\u00cc\t\2\2\2\u00cb\u00ca\3\2\2\2"+
		"\u00cc\u00cd\3\2\2\2\u00cd\u00cb\3\2\2\2\u00cd\u00ce\3\2\2\2\u00ceH\3"+
		"\2\2\2\u00cf\u00d4\5+\26\2\u00d0\u00d4\5-\27\2\u00d1\u00d4\5/\30\2\u00d2"+
		"\u00d4\5\61\31\2\u00d3\u00cf\3\2\2\2\u00d3\u00d0\3\2\2\2\u00d3\u00d1\3"+
		"\2\2\2\u00d3\u00d2\3\2\2\2\u00d4J\3\2\2\2\u00d5\u00d8\5\63\32\2\u00d6"+
		"\u00d8\5\65\33\2\u00d7\u00d5\3\2\2\2\u00d7\u00d6\3\2\2\2\u00d8L\3\2\2"+
		"\2\u00d9\u00dd\5#\22\2\u00da\u00dd\5%\23\2\u00db\u00dd\5\67\34\2\u00dc"+
		"\u00d9\3\2\2\2\u00dc\u00da\3\2\2\2\u00dc\u00db\3\2\2\2\u00ddN\3\2\2\2"+
		"\u00de\u00e1\5\'\24\2\u00df\u00e1\5)\25\2\u00e0\u00de\3\2\2\2\u00e0\u00df"+
		"\3\2\2\2\u00e1P\3\2\2\2\u00e2\u00e5\5A!\2\u00e3\u00e5\5? \2\u00e4\u00e2"+
		"\3\2\2\2\u00e4\u00e3\3\2\2\2\u00e5R\3\2\2\2\u00e6\u00e7\7c\2\2\u00e7\u00e8"+
		"\7n\2\2\u00e8\u00e9\7n\2\2\u00e9\u00ea\7q\2\2\u00ea\u00eb\7e\2\2\u00eb"+
		"T\3\2\2\2\u00ec\u00ed\7k\2\2\u00ed\u00ee\7p\2\2\u00ee\u00ef\7r\2\2\u00ef"+
		"\u00f0\7w\2\2\u00f0\u00f1\7v\2\2\u00f1V\3\2\2\2\u00f2\u00f3\7y\2\2\u00f3"+
		"\u00f4\7j\2\2\u00f4\u00f5\7k\2\2\u00f5\u00f6\7n\2\2\u00f6\u00f7\7g\2\2"+
		"\u00f7X\3\2\2\2\u00f8\u00f9\7k\2\2\u00f9\u00fa\7h\2\2\u00faZ\3\2\2\2\u00fb"+
		"\u00fc\7h\2\2\u00fc\u00fd\7q\2\2\u00fd\u00fe\7t\2\2\u00fe\\\3\2\2\2\u00ff"+
		"\u0100\7g\2\2\u0100\u0101\7n\2\2\u0101\u0102\7u\2\2\u0102\u0103\7g\2\2"+
		"\u0103^\3\2\2\2\u0104\u0105\7x\2\2\u0105\u0106\7c\2\2\u0106\u0107\7t\2"+
		"\2\u0107`\3\2\2\2\u0108\u0109\7t\2\2\u0109\u010a\7g\2\2\u010a\u010b\7"+
		"v\2\2\u010b\u010c\7w\2\2\u010c\u010d\7t\2\2\u010d\u010e\7p\2\2\u010eb"+
		"\3\2\2\2\u010f\u0110\7p\2\2\u0110\u0111\7w\2\2\u0111\u0112\7n\2\2\u0112"+
		"\u0113\7n\2\2\u0113d\3\2\2\2\u0114\u0115\7q\2\2\u0115\u0116\7w\2\2\u0116"+
		"\u0117\7v\2\2\u0117\u0118\7r\2\2\u0118\u0119\7w\2\2\u0119\u011a\7v\2\2"+
		"\u011af\3\2\2\2\u011b\u011c\7g\2\2\u011c\u011d\7t\2\2\u011d\u011e\7t\2"+
		"\2\u011e\u011f\7q\2\2\u011f\u0120\7t\2\2\u0120h\3\2\2\2\u0121\u0122\7"+
		"v\2\2\u0122\u0123\7t\2\2\u0123\u0124\7w\2\2\u0124\u0125\7g\2\2\u0125j"+
		"\3\2\2\2\u0126\u0127\7h\2\2\u0127\u0128\7c\2\2\u0128\u0129\7n\2\2\u0129"+
		"\u012a\7u\2\2\u012a\u012b\7g\2\2\u012bl\3\2\2\2\u012c\u012d\7p\2\2\u012d"+
		"\u012e\7q\2\2\u012e\u012f\7v\2\2\u012fn\3\2\2\2\u0130\u0131\7c\2\2\u0131"+
		"\u0132\7p\2\2\u0132\u0133\7f\2\2\u0133p\3\2\2\2\u0134\u0135\7q\2\2\u0135"+
		"\u0136\7t\2\2\u0136r\3\2\2\2\u0137\u013b\t\3\2\2\u0138\u013a\t\4\2\2\u0139"+
		"\u0138\3\2\2\2\u013a\u013d\3\2\2\2\u013b\u0139\3\2\2\2\u013b\u013c\3\2"+
		"\2\2\u013ct\3\2\2\2\u013d\u013b\3\2\2\2\u013e\u0140\t\5\2\2\u013f\u013e"+
		"\3\2\2\2\u0140\u0141\3\2\2\2\u0141\u013f\3\2\2\2\u0141\u0142\3\2\2\2\u0142"+
		"\u0143\3\2\2\2\u0143\u0144\b;\2\2\u0144v\3\2\2\2\u0145\u0146\7\61\2\2"+
		"\u0146\u0147\7,\2\2\u0147\u014b\3\2\2\2\u0148\u014a\13\2\2\2\u0149\u0148"+
		"\3\2\2\2\u014a\u014d\3\2\2\2\u014b\u014c\3\2\2\2\u014b\u0149\3\2\2\2\u014c"+
		"\u014e\3\2\2\2\u014d\u014b\3\2\2\2\u014e\u014f\7,\2\2\u014f\u0150\7\61"+
		"\2\2\u0150\u0151\3\2\2\2\u0151\u0152\b<\2\2\u0152x\3\2\2\2\u0153\u0154"+
		"\7\61\2\2\u0154\u0155\7\61\2\2\u0155\u0159\3\2\2\2\u0156\u0158\n\6\2\2"+
		"\u0157\u0156\3\2\2\2\u0158\u015b\3\2\2\2\u0159\u0157\3\2\2\2\u0159\u015a"+
		"\3\2\2\2\u015a\u015c\3\2\2\2\u015b\u0159\3\2\2\2\u015c\u015d\b=\2\2\u015d"+
		"z\3\2\2\2\16\2\u00c8\u00cd\u00d3\u00d7\u00dc\u00e0\u00e4\u013b\u0141\u014b"+
		"\u0159\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}