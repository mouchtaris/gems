require 'optparse'
class Cyr
  class Args
    def initialize(args)
      @args = args
    end

    def root
      @root ||= (
        case root = args[0]
        when Pathname
          root.tap { |root| root.directory? || raise }
        when String 
          File.directory?(root) || raise
          Pathname.new(root)
        else
          raise ArgumentError, "root:#{root.inspect}"
        end
      )
    end
  end

  def initialize(args)
    @args = Args.new(args)
  end

  def workspace
    @workspace ||= (
      require_relative 'workspace'
      Workspace.new(@args.root)
    )
  end
end
